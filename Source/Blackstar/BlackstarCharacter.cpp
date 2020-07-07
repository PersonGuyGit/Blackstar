// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BlackstarCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABlackstarCharacter::Pause()
{
}

ABlackstarCharacter::ABlackstarCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);


	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	// 6/19/2020 Added crouching to this block
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABlackstarCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlackstarCharacter::MoveRight);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABlackstarCharacter::Interact);

	// make a function in ABlackstarCharacter instead?

	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacter::Crouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacter::Crouch);



	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABlackstarCharacter::Sprint);

	//PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABlackstarCharacter::Pause);

	//PlayerInputComponent->BindAxis("Aim Up", this, &ABlackstarCharacter::AimUp);
	//PlayerInputComponent->BindAxis("Aim Right", this, &ABlackstarCharacter::AimRight);


	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABlackstarCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ABlackstarCharacter::EndCrouch);



	//set up gameplay bindings, relating to combat
	//PlayerInputComponent->BindAction("Fire", this, &AWeapon::Fire);
	//PlayerInputComponent->BindAction("Alt Fire", this, &AWeapon::AltFire);
	//PlayerInputComponent->BindAction("Weapon Wheel", this, &AWeapon::WeaponWheel);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &ABlackstarCharacter::Block);



	//set up gameplay bindings related to touch controls

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABlackstarCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABlackstarCharacter::TouchStopped);
}


void ABlackstarCharacter::BeginCrouch()
{
	Crouch();
}

void ABlackstarCharacter::EndCrouch()
{
	UnCrouch();
}
void ABlackstarCharacter::Interact()
{
}

void ABlackstarCharacter::Block()
{
}

void ABlackstarCharacter::Sprint()
{
}

void ABlackstarCharacter::AimUp()
{
}

void ABlackstarCharacter::AimRight()
{


}

void ABlackstarCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ABlackstarCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ABlackstarCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

