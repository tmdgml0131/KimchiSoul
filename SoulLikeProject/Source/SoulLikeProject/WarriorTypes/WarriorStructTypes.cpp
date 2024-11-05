// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorStructTypes.h"
#include "SoulLikeProject/AbilitySystem/Abilities/WarriorGameplayAbility.h"

bool FWarriorHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
