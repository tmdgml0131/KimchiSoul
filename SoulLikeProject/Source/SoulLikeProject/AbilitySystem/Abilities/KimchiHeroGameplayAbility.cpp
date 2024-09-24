// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiHeroGameplayAbility.h"
#include "SoulLikeProject/Character/KimchiHeroCharacter.h"
#include "SoulLikeProject/Controller/KimchiHeroController.h"

AKimchiHeroCharacter* UKimchiHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if(!CachedKimchiHeroCharacter.IsValid())
	{
		CachedKimchiHeroCharacter = Cast<AKimchiHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedKimchiHeroCharacter.IsValid()? CachedKimchiHeroCharacter.Get() : nullptr;
}

AKimchiHeroController* UKimchiHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if(!CachedKimchiHeroController.IsValid())
	{
		CachedKimchiHeroController = Cast<AKimchiHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedKimchiHeroController.IsValid()? CachedKimchiHeroController.Get() : nullptr;
}

UHeroCombatComponent* UKimchiHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
