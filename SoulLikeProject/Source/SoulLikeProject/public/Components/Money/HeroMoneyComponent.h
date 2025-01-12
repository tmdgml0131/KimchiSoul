// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"

///////////////////////////////////////////////////
#include "HeroMoneyComponent.generated.h"

class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UHeroMoneyComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<AWarriorHeroCharacter> WarriorHeroCharacter;

	UFUNCTION(BlueprintPure, Category="Hero|Money")
	int32 GetMoneyAmount() const { return MoneyAmount; }
private:
	// Negative Value is not allowed
	UPROPERTY(VisibleAnywhere, Category="Hero|Money")
	uint32 MoneyAmount = 0;
	
	UFUNCTION(BlueprintCallable, Category="Hero|Money")
	void AddMoney(const int32 Amount);
	
	UFUNCTION(BlueprintCallable, Category="Hero|Money")
	void RemoveMoney(const int32 Amount);
};
