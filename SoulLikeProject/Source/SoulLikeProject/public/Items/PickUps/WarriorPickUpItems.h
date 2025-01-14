// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/WarriorPickUpBase.h"
#include "WarriorPickUpItems.generated.h"

class UGameplayEffect;
class UWarriorAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class SOULLIKEPROJECT_API AWarriorPickUpItems : public AWarriorPickUpBase
{
	GENERATED_BODY()
	
public:
	void PickUp(UWarriorAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);
	
protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Item Picked Up"))
	void BP_OnItemPickedUp();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> ItemGameplayEffectClass;
};
