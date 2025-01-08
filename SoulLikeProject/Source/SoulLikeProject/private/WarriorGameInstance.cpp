// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorGameInstance.h"

TSoftObjectPtr<UWorld> UWarriorGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for(const FWarriorGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if(!GameLevelSet.Isvalid()) continue;

		if(GameLevelSet.LevelTag == InTag)
		{
			return GameLevelSet.Level;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Invalid Level Data"));
	return TSoftObjectPtr<UWorld>();
}
