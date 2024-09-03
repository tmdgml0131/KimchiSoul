// Fill out your copyright notice in the Description page of Project Settings.


#include "KimchiCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../DataAssets/Input/DataAsset_InputConfig.h"
#include "../Components/Input/KimchiInputComponent.h"
#include "../KimchiGameplayTags.h"

#define PARAGON

AKimchiCharacter::AKimchiCharacter()
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
}

void AKimchiCharacter::BeginPlay()
{
	Super::BeginPlay();

#ifdef PARAGON
	for (const FName& BoneName : BonesToHide)
	{
		GetMesh()->HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	}
#endif
}

void AKimchiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	checkf(InputConfigDataAsset, TEXT("No InputConfigDataAsset!!"));
	
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	checkf(Subsystem, TEXT("Subsystem is nullptr"));
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UKimchiInputComponent* KimchiInputComponent = CastChecked<UKimchiInputComponent>(PlayerInputComponent);

	KimchiInputComponent->BindNativeInputAction(InputConfigDataAsset, KimchiGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	KimchiInputComponent->BindNativeInputAction(InputConfigDataAsset, KimchiGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	KimchiInputComponent->BindNativeInputAction(InputConfigDataAsset, KimchiGameplayTags::InputTag_Jump, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);
}

void AKimchiCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(KimchiAbilitySystemComponent && KimchiAttributeSet)
	{
		
	}
}

void AKimchiCharacter::Input_Move(const FInputActionValue& InputActionValue)
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

void AKimchiCharacter::Input_Look(const FInputActionValue& InputActionValue)
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

void AKimchiCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Super::Jump();
}
