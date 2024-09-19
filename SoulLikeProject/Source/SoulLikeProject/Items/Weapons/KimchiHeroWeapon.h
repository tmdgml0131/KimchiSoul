// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KimchiWeaponBase.h"
#include "SoulLikeProject/KimchiTypes/KimchiStructTypes.h"

////////////////////////////////////////
#include "KimchiHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API AKimchiHeroWeapon : public AKimchiWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FKimchiHeroWeaponData HeroWeaponData;
};
