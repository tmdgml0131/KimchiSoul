// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KimchiBaseCharacter.h"
#include "KimchiCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API AKimchiCharacter : public AKimchiBaseCharacter
{
	GENERATED_BODY()

public:
	AKimchiCharacter();
	
private:
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	
#pragma endregion
};
