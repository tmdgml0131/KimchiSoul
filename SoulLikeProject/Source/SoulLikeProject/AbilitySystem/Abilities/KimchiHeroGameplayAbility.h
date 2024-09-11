// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KimchiGameplayAbility.h"
#include "KimchiHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class AKimchiHeroController;
class AKimchiHeroCharacter;
/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UKimchiHeroGameplayAbility : public UKimchiGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Kimchi|Ability")
	AKimchiHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Kimchi|Ability")
	AKimchiHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Kimchi|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AKimchiHeroCharacter> CachedKimchiHeroCharacter;
	TWeakObjectPtr<AKimchiHeroController> CachedKimchiHeroController;
};
