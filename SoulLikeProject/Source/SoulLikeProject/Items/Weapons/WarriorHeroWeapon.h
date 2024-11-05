// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "WarriorWeaponBase.h"
#include "SoulLikeProject/WarriorTypes/WarriorStructTypes.h"

////////////////////////////////////////
#include "WarriorHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarriorHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
	
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
