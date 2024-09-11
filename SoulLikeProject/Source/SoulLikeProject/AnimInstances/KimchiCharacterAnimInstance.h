// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KimchiBaseAnimInstance.h"
#include "KimchiCharacterAnimInstance.generated.h"

class AKimchiBaseCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UKimchiCharacterAnimInstance : public UKimchiBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	AKimchiBaseCharacter* OwningCharacter;
	
	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bIsInAir;
};
