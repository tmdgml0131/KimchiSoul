// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiAbilitySystemComponent.h"
#include "SoulLikeProject/AbilitySystem/Abilities/KimchiGameplayAbility.h"

void UKimchiAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid()) return;
	
	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UKimchiAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	
}

void UKimchiAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FKimchiHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if(InDefaultWeaponAbilities.IsEmpty()) return;

	for(const FKimchiHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if(!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}
