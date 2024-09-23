// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartUpDataBase.h"
#include "SoulLikeProject/KimchiTypes/KimchiStructTypes.h"
/////////////////////////////////////////////
#include "DataAsset_KimchiStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UDataAsset_KimchiStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKimchiAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FKimchiHeroAbilitySet> HeroStartUpAbilitySets;
};
