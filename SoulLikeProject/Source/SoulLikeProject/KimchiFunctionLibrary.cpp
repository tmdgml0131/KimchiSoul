// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/KimchiAbilitySystemComponent.h"

UKimchiAbilitySystemComponent* UKimchiFunctionLibrary::NativeGetKimchiASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UKimchiAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UKimchiFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UKimchiAbilitySystemComponent* ASC = NativeGetKimchiASCFromActor(InActor);
	
	if(!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UKimchiFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UKimchiAbilitySystemComponent* ASC = NativeGetKimchiASCFromActor(InActor);

	if(ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UKimchiFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UKimchiAbilitySystemComponent* ASC = NativeGetKimchiASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UKimchiFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
	EKimchiConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck)? EKimchiConfirmType::YES : EKimchiConfirmType::NO; 
}
