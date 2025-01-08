// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"
#include "Engine/AssetManager.h"
#include "Character/WarriorEnemyCharacter.h"
#include "NavigationSystem.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility,
                                                                               FGameplayTag EventTag, TSoftClassPtr<AWarriorEnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn,
                                                                               const FVector& SpawnOrigin, float RandomSpawnRadius)
{
	UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>(OwningAbility);
	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnOrigin = SpawnOrigin;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;
	
	return Node;
}

void UAbilityTask_WaitSpawnEnemies::Activate()
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

	DelegateHandle = Delegate.AddUObject(this, &ThisClass::OnGameplayEventReceived);
}

void UAbilityTask_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	Delegate.Remove(DelegateHandle);
	
	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InpayLoad)
{
	if(CachedSoftEnemyClassToSpawn.IsNull())
	{
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AWarriorEnemyCharacter*>());
		}
		EndTask();
		return;
	}
	
	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		CachedSoftEnemyClassToSpawn.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded)
	);
}

void UAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded()
{
	UClass* LoadedClass = CachedSoftEnemyClassToSpawn.Get();
	UWorld* World = GetWorld();

	if(!LoadedClass || !World)
	{
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AWarriorEnemyCharacter*>());
		}
		EndTask();
		return;
	}

	TArray<AWarriorEnemyCharacter*> SpawnedEnemies;
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Spawn and Add to SpawnedEnemies TArray
	for(int32 i = 0; i < CachedNumToSpawn; i++)
	{
		FVector RandomLocation;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, CachedSpawnOrigin, RandomLocation, CachedRandomSpawnRadius);
		RandomLocation += FVector(0.f, 0.f, 450.f);
		const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

		AWarriorEnemyCharacter* SpawnedEnemy = World->SpawnActor<AWarriorEnemyCharacter>(LoadedClass, RandomLocation, SpawnFacingRotation, SpawnParam);
		if(SpawnedEnemy)
		{
			SpawnedEnemies.Add(SpawnedEnemy);
		}
	}

	if(ShouldBroadcastAbilityTaskDelegates())
	{
		if(!SpawnedEnemies.IsEmpty())
		{
			OnSpawnFinished.Broadcast(SpawnedEnemies);
		}
		else
		{
			DidNotSpawn.Broadcast(TArray<AWarriorEnemyCharacter*>());
		}
	}
	EndTask();
}
