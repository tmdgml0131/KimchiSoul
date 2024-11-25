// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/WarriorAIController.h"

#include "Navigation/CrowdFollowingComponent.h"

AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if(UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ads"));
	}
}
