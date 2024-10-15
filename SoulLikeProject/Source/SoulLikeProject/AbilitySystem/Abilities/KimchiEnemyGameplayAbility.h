// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KimchiGameplayAbility.h"
#include "KimchiEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AKimchiEnemyCharacter;
/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UKimchiEnemyGameplayAbility : public UKimchiGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Kimchi|Ability")
	AKimchiEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Kimchi|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AKimchiEnemyCharacter> CachedEnemyCharacter;
};
