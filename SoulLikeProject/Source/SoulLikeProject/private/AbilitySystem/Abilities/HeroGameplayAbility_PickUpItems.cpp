// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_PickUpItems.h"

#include "Character/WarriorHeroCharacter.h"
#include "Components/UI/HeroUIComponent.h"
#include "Items/PickUps/WarriorPickUpItems.h"
#include "Kismet/KismetSystemLibrary.h"

void UHeroGameplayAbility_PickUpItems::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GetHeroUIComponentFromActorInfo()->OnItemInteracted.Broadcast(true);
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_PickUpItems::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetHeroUIComponentFromActorInfo()->OnItemInteracted.Broadcast(false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_PickUpItems::CollectItems()
{
	CollectedItems.Empty();
	
	TArray<FHitResult> TraceHits;
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + -(GetHeroCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance),
		TraceBoxSize / 2.f,
		(-GetHeroCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		ItemsTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for(const FHitResult& TraceHit: TraceHits)
	{
		if(AWarriorPickUpItems* FoundItems = Cast<AWarriorPickUpItems>(TraceHit.GetActor()))
		{
			CollectedItems.AddUnique(FoundItems);
		}
	}

	if(CollectedItems.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UHeroGameplayAbility_PickUpItems::PickUpItems()
{
	if(CollectedItems.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}

	for(AWarriorPickUpItems* CollectedItem: CollectedItems)
	{
		if(CollectedItem)
		{
			CollectedItem->PickUp(GetWarriorAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
	}
}
