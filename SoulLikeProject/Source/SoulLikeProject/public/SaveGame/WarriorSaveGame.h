// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WarriorTypes/WarriorEnumTypes.h"
#include "WarriorSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UWarriorSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	EWarriorGameDifficulty SavedCurrentGameDifficulty;
};
