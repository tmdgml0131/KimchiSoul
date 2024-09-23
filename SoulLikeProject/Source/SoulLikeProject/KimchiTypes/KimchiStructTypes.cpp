// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiStructTypes.h"
#include "SoulLikeProject/AbilitySystem/Abilities/KimchiGameplayAbility.h"

bool FKimchiHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
