// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_PickUpItems.generated.h"

class AWarriorPickUpItems;
/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UHeroGameplayAbility_PickUpItems : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void CollectItems();

	UFUNCTION(BlueprintCallable)
	void PickUpItems();
private:
	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f;
	
	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> ItemsTraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugShape;

	UPROPERTY()
	TArray<AWarriorPickUpItems*> CollectedItems;
	
};
