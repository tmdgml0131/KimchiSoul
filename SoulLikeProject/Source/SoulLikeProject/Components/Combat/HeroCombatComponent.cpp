// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"

#include "SoulLikeProject/Items/Weapons/KimchiHeroWeapon.h"

AKimchiHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
 	return Cast<AKimchiHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
