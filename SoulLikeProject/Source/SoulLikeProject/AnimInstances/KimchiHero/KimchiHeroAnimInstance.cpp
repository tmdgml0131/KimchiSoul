// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiHeroAnimInstance.h"

#include "SoulLikeProject/Character/KimchiCharacter.h"

void UKimchiHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if(OwningCharacter)
	{
		OwningHeroCharacter = Cast<AKimchiCharacter>(OwningCharacter);
	}
}

void UKimchiHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(bHasAcceleration || bIsInAir)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
