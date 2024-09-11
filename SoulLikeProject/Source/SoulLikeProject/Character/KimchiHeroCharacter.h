// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KimchiBaseCharacter.h"
#include "KimchiHeroCharacter.generated.h"

struct FInputActionValue;
class UHeroCombatComponent;
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
class UInputComponent;

/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API AKimchiHeroCharacter : public AKimchiBaseCharacter
{
	GENERATED_BODY()

public:
	AKimchiHeroCharacter();
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
private:
	UPROPERTY(EditAnywhere, Category = "Bones")
	TArray<FName> BonesToHide;
	
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;
#pragma endregion
	
#pragma region Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Jump(const FInputActionValue& InputActionValue);
#pragma endregion

public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const {return HeroCombatComponent;}
};




