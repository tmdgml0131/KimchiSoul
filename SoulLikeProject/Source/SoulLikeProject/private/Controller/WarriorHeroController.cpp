// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/WarriorHeroController.h"

AWarriorHeroController::AWarriorHeroController()
{
	// Player will use PlayerID: 0
	HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AWarriorHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}
