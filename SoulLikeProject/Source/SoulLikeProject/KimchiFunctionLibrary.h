// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KimchiFunctionLibrary.generated.h"

struct FGameplayTag;
class UKimchiAbilitySystemComponent;

UENUM()
enum class EKimchiConfirmType : uint8
{
	YES,
	NO
};

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UKimchiFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UKimchiAbilitySystemComponent* NativeGetKimchiASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Kimchi|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Kimchi|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Kimchi|FunctionLibrary", meta = (DisplayName = "DoesActorHaveTag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EKimchiConfirmType& OutConfirmType);
};
