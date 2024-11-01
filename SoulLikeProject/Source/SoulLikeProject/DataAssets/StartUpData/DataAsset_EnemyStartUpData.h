// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartUpDataBase.h"
#include "SoulLikeProject/AbilitySystem/Abilities/KimchiEnemyGameplayAbility.h"
#include "DataAsset_EnemyStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKimchiAbilitySystemComponent* InASCToGive, int32 ApplyLevel) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UKimchiEnemyGameplayAbility>> EnemyCombatAilities;
};
