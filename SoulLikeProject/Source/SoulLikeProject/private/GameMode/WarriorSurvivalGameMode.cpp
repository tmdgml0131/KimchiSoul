// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/WarriorSurvivalGameMode.h"

void AWarriorSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(!EnemyWaveSpawnerDataTable) return;

	SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::WaitSpawnNewWave);
	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
}

void AWarriorSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CurrentSurvivalGameModeState == EWarriorSurvivalGameModeState::WaitSpawnNewWave)
	{
		TImePassedSinceStart += DeltaSeconds;
		if(TImePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TImePassedSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::SpawningNewWave);
		}
	}

	if(CurrentSurvivalGameModeState == EWarriorSurvivalGameModeState::SpawningNewWave)
	{
		TImePassedSinceStart += DeltaSeconds;
		if(TImePassedSinceStart >= SpawnEnemiesDelayTime)
		{
			TImePassedSinceStart = 0.f;
			//TODO: Handle Spawn New Enemy
			SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::InProgress);
		}
	}

	if(CurrentSurvivalGameModeState == EWarriorSurvivalGameModeState::WaveCompleted)
	{
		TImePassedSinceStart += DeltaSeconds;
		if(TImePassedSinceStart >= WaveCompletedWaitTime)
		{
			TImePassedSinceStart = 0.f;
			CurrentWaveCount++;
			if(HasFinishedAllWaves())
			{
				SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::AllWavesDone);
			}
			else
			{
				SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState::WaitSpawnNewWave);
			}
		}
	}
}

void AWarriorSurvivalGameMode::SetCurrentSurvivalGameModeState(EWarriorSurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;
	OnSurvivalGameModeStateChanged.Broadcast(CurrentSurvivalGameModeState);
}

bool AWarriorSurvivalGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}
