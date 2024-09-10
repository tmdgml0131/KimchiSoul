// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoulLikeProject/Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"

///////////////////////////////////////
#include "PawnCombatComponent.generated.h"

class AKimchiWeaponBase;
/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Kimchi|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,AKimchiWeaponBase* InWeaponToRegister,bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Kimchi|Combat")
	AKimchiWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "Kimchi|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Kimchi|Combat")
	AKimchiWeaponBase* GetCharacterCurrentEquippedWeapon() const;

private:
	TMap<FGameplayTag,AKimchiWeaponBase*> CharacterCarriedWeaponMap;
};