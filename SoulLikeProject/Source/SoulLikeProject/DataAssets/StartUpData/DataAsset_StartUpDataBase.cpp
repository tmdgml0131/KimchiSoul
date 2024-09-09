// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_StartUpDataBase.h"
#include "../../AbilitySystem/Abilities/KimchiGameplayAbility.h"
#include "../../AbilitySystem/KimchiAbilitySystemComponent.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UKimchiAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UKimchiGameplayAbility>>& InAbilitiesToGive,
	UKimchiAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if(InAbilitiesToGive.IsEmpty()) return;

	for(const TSubclassOf<UKimchiGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if(!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
