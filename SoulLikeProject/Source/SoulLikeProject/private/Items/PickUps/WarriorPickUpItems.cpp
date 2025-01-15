// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/WarriorPickUpItems.h"

#include "GameplayEffect.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Character/WarriorHeroCharacter.h"
#include "Components/SphereComponent.h"

AWarriorPickUpItems::AWarriorPickUpItems()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	PickUpCollisionSphere->SetupAttachment(GetRootComponent());
}

void AWarriorPickUpItems::PickUp(UWarriorAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	UE_LOG(LogTemp, Error, TEXT("Forgot to Assign ItemGameplayEffectClass!"));
	if(!ItemGameplayEffectClass) return;
	
	UGameplayEffect* EffectCDO = ItemGameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	AbilitySystemComponent->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, AbilitySystemComponent->MakeEffectContext());

	BP_OnItemPickedUp();
}

void AWarriorPickUpItems::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AWarriorHeroCharacter* HeroCharacter = Cast<AWarriorHeroCharacter>(OtherActor))
	{
		HeroCharacter->GetWarriorAbilitySystemComponent()->TryActivateAbilityByTag(WarriorGameplayTags::Player_Ability_PickUp_Items);
	}
}

void AWarriorPickUpItems::BP_OnItemAddedToInventory()
{
	BP_OnItemPickedUp();
}
