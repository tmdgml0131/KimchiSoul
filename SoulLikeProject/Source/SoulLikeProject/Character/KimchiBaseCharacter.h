// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "KimchiBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UKimchiAbilitySystemComponent;
class UKimchiAttributeSet;

UCLASS()
class SOULLIKEPROJECT_API AKimchiBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKimchiBaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const; 
protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UKimchiAbilitySystemComponent*  KimchiAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UKimchiAttributeSet* KimchiAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;
	
public:
	FORCEINLINE UKimchiAbilitySystemComponent* GetKimchiAbilitySystemComponent() const {return KimchiAbilitySystemComponent;}
	FORCEINLINE UKimchiAttributeSet* GetKimchiAttributeSet() const {return KimchiAttributeSet;}
};
