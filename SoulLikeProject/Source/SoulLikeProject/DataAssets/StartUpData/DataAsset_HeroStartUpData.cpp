// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_HeroStartUpData.h"

#include "SoulLikeProject/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "SoulLikeProject/AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UDataAsset_WarriorStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
                                                                int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for(const FWarriorHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if(!AbilitySet.IsValid()) continue;;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
