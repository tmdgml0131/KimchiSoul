// Fill out your copyright notice in the Description page of Project Settings.



#include "Character/WarriorHeroCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WarriorFunctionLibrary.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/WarriorInputComponent.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/UI/HeroUIComponent.h"

#define PARAGON

AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	// Character CapsuleComponents Initial Settings 
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Character Controller Rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// CameraBoom Initial Settings
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	// FollowCamera Initial Settings
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Character Movement Initial Settings
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
	
}

UPawnCombatComponent* AWarriorHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* AWarriorHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* AWarriorHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

#ifdef PARAGON
	for (const FName& BoneName : BonesToHide)
	{
		GetMesh()->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	}
#endif
}

void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("No InputConfigDataAsset!!"));
	
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	checkf(Subsystem, TEXT("Subsystem is nullptr"));
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UWarriorInputComponent* WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);

	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);
	
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_PickUp, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStarted);
	//WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Dash, ETriggerEvent::Started, this, &ThisClass::Input_DashStarted);
	//WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Dash, ETriggerEvent::Completed, this, &ThisClass::Input_DashFinished);
	//WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Jump, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);

	WarriorInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Bcs its Soft-Reference, null-check not Validation
	if(!CharacterStartUpData.IsNull())
	{
		if(UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
		}
	}
}

void AWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if(MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if(MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if(LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if(LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWarriorHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AWarriorHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X>0.f? WarriorGameplayTags::Player_Event_SwitchTarget_Right : WarriorGameplayTags::Player_Event_SwitchTarget_Left,
		Data
		);

}

void AWarriorHeroCharacter::Input_PickUpStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, WarriorGameplayTags::Player_Event_PickUp, Data);
}

void AWarriorHeroCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Super::Jump();
}

//void AWarriorHeroCharacter::Input_DashStarted(const FInputActionValue& InputActionValue)
//{
//	if(!GetCharacterMovement()) return;
//	
//	GetCharacterMovement()->MaxWalkSpeed = 600.f;
//}
//
//void AWarriorHeroCharacter::Input_DashFinished(const FInputActionValue& InputActionValue)
//{
//	if(!GetCharacterMovement()) return;
//
//	if(UWarriorFunctionLibrary::NativeDoesActorHaveTag(this, WarriorGameplayTags::Player_Status_TargetLock))
//	{
//		GetCharacterMovement()->MaxWalkSpeed = 200.f;
//	}
//	else
//	{
//		GetCharacterMovement()->MaxWalkSpeed = 400.f;
//	}
//}

void AWarriorHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	WarriorAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AWarriorHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	WarriorAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
