// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorTypes/WarriorEnumTypes.h"

//////////////////////////////////////////
#include "WarriorFunctionLibrary.generated.h"

class UWarriorGameInstance;
struct FScalableFloat;
class UPawnCombatComponent;
struct FGameplayTag;
class UWarriorAbilitySystemComponent;
class AWarriorHeroCharacter;

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UWarriorAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta = (DisplayName = "DoesActorHaveTag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EWarriorValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta =(Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
		float& OutRemainingTime, EWarriorCountDownActionInput CountDownInput,
		UPARAM(DisplayName = "Output") EWarriorCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
	static int32 GetGameDifficulty(UWorld* InWorldData, bool bIsPlayer);

	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UWarriorGameInstance* GetWarriorGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(EWarriorInputMode InInputMode, const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
	static void SaveCurrentGameDifficulty(EWarriorGameDifficulty InDifficultyToSave);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
	static bool TryLoadSavedGameDifficulty(EWarriorGameDifficulty& OutSavedDifficulty);
};
