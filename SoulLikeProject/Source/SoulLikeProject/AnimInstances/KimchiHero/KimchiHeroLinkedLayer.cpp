// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiHeroLinkedLayer.h"
#include "KimchiHeroAnimInstance.h"

UKimchiHeroAnimInstance* UKimchiHeroLinkedLayer::GetHeroAnimInstance() const
{
	return Cast<UKimchiHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
