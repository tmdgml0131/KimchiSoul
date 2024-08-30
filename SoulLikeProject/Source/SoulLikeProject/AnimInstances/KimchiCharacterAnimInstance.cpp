// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiCharacterAnimInstance.h"

#include "SoulLikeProject/Character/KimchiBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UKimchiCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningCharacter = Cast<AKimchiBaseCharacter>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UKimchiCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(!OwningCharacter || !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
