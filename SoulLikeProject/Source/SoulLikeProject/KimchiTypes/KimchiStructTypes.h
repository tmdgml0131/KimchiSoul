// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


/////////////////////////////////////////
#include "KimchiStructTypes.generated.h"

class UKimchiHeroLinkedLayer;

USTRUCT(BlueprintType)
struct FKimchiHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UKimchiHeroLinkedLayer> WeaponAnimLayerToLink;
};