// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiEnemyGameplayAbility.h"

#include "SoulLikeProject/Character/KimchiEnemyCharacter.h"

AKimchiEnemyCharacter* UKimchiEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if(!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AKimchiEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UKimchiEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
