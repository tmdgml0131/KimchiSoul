// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Money/HeroMoneyComponent.h"
#include "Character/WarriorHeroCharacter.h"
#include "Components/UI/HeroUIComponent.h"

void UHeroMoneyComponent::AddMoney(const int32 Amount)
{
	if(!WarriorHeroCharacter.IsValid() || !WarriorHeroCharacter->GetHeroUIComponent()) return;
		
	if (Amount > 0)
	{
		MoneyAmount += Amount;
		WarriorHeroCharacter->GetHeroUIComponent()->OnHeroMoneyAmountChanged.Broadcast(MoneyAmount);
	}
}

void UHeroMoneyComponent::RemoveMoney(const int32 Amount)
{
	if(!WarriorHeroCharacter.IsValid() || WarriorHeroCharacter->GetHeroUIComponent()) return;
	
	if (Amount > 0)
	{
		MoneyAmount = FMath::Clamp(MoneyAmount - Amount, 0, MoneyAmount);
		
		WarriorHeroCharacter->GetHeroUIComponent()->OnHeroMoneyAmountChanged.Broadcast(MoneyAmount);
	}
}
