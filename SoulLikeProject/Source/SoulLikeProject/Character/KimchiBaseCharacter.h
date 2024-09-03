// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "KimchiBaseCharacter.generated.h"

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
	class UKimchiAbilitySystemComponent*  KimchiAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	class UKimchiAttributeSet* KimchiAttributeSet;

public:
	FORCEINLINE UKimchiAbilitySystemComponent* GetKimchiAbilitySystemComponent() const {return KimchiAbilitySystemComponent;}
	FORCEINLINE UKimchiAttributeSet* GetKimchiAttributeSet() const {return KimchiAttributeSet;}
};
