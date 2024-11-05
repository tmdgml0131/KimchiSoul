// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorHeroLinkedLayer.h"
#include "WarriorHeroAnimInstance.h"

UWarriorHeroAnimInstance* UWarriorHeroLinkedLayer::GetHeroAnimInstance() const
{
	return Cast<UWarriorHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
