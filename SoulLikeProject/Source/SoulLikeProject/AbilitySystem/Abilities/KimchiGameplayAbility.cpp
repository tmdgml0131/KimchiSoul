// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiGameplayAbility.h"
#include "SoulLikeProject/AbilitySystem/KimchiAbilitySystemComponent.h"
#include "SoulLikeProject/Components/Combat/PawnCombatComponent.h"

void UKimchiGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if(ActorInfo && !Spec.IsActive() && AbilityActivationPolicy == EKimchiAbilityActivationPolicy::OnGiven)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UKimchiGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(AbilityActivationPolicy == EKimchiAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UKimchiGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UKimchiAbilitySystemComponent* UKimchiGameplayAbility::GetKimchiAbilitySystemComponentFromActorInfo() const
{
	return Cast<UKimchiAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
