// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartUpDataBase.h"
#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "DataAsset_EnemyStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorEnemyGameplayAbility>> EnemyCombatAilities;
};
