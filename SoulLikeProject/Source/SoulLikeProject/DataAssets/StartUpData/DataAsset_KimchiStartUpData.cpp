// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_KimchiStartUpData.h"

#include "SoulLikeProject/AbilitySystem/KimchiAbilitySystemComponent.h"
#include "SoulLikeProject/AbilitySystem/Abilities/KimchiGameplayAbility.h"

void UDataAsset_KimchiStartUpData::GiveToAbilitySystemComponent(UKimchiAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for(const FKimchiHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if(!AbilitySet.IsValid()) continue;;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
