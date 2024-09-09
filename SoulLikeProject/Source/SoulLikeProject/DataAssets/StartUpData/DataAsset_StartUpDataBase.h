// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UKimchiAbilitySystemComponent;
class UKimchiGameplayAbility;
/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKimchiAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UKimchiGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UKimchiGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UKimchiGameplayAbility>>& InAbilitiesToGive, UKimchiAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
