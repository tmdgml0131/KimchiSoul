// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorGameInstance.h"
#include "MoviePlayer.h"
void UWarriorGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorldLoaded);
}

void UWarriorGameInstance::OnPreLoadMap(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.f;
	LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UWarriorGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}

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
