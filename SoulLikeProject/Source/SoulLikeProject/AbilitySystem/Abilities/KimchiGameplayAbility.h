// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "KimchiGameplayAbility.generated.h"

class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EKimchiAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};
/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UKimchiGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "KimchiAbility")
	EKimchiAbilityActivationPolicy AbilityActivationPolicy = EKimchiAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Kimchi|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;
	
};
