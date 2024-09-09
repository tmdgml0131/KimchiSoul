// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiBaseCharacter.h"

#include "SoulLikeProject/AbilitySystem/KimchiAbilitySystemComponent.h"
#include "SoulLikeProject/AbilitySystem/KimchiAttributeSet.h"

// Sets default values
AKimchiBaseCharacter::AKimchiBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	KimchiAbilitySystemComponent = CreateDefaultSubobject<UKimchiAbilitySystemComponent>(TEXT("KimchiAbilitySystem"));
	KimchiAttributeSet = CreateDefaultSubobject<UKimchiAttributeSet>(TEXT("KimchiAttributeSet"));
}

UAbilitySystemComponent* AKimchiBaseCharacter::GetAbilitySystemComponent() const
{
	return GetKimchiAbilitySystemComponent();
}

void AKimchiBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(KimchiAbilitySystemComponent)
	{
		KimchiAbilitySystemComponent->InitAbilityActorInfo(this, this);

		// If null, throw break-point
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot To Assign StartUp Data to %s"), *GetName());
	}
}

