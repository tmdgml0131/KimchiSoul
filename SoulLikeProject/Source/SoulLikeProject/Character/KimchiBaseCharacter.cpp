// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiBaseCharacter.h"

// Sets default values
AKimchiBaseCharacter::AKimchiBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
}

// Called when the game starts or when spawned
void AKimchiBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKimchiBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKimchiBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

