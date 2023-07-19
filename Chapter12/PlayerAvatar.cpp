// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PangaeaAnimInstance.h"

APlayerAvatar::APlayerAvatar()
{
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	auto characterMovement = GetCharacterMovement();
	characterMovement->bOrientRotationToMovement = true; // Rotate character to moving direction
	characterMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	characterMovement->bConstrainToPlane = true;
	characterMovement->bSnapToPlaneAtStart = true;

	// Create the camera spring arm
	_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_SpringArmComponent->SetupAttachment(RootComponent);		//Attach to the character root
	_SpringArmComponent->SetUsingAbsoluteRotation(true);		//Don't rotate the arm with the character
	_SpringArmComponent->TargetArmLength = 800.f;				//Set the arm's length 
	_SpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	//Set the arm's rotation (60 degree up)
	_SpringArmComponent->bDoCollisionTest = false;				//No collision test

	// Create the camera
	_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_CameraComponent->SetupAttachment(_SpringArmComponent, USpringArmComponent::SocketName);
	//Attach to the spring arm
	_CameraComponent->bUsePawnControlRotation = false;			//Camera rotation is not controllable  
}

void APlayerAvatar::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerAvatar::AttachWeapon(AWeapon* Weapon)
{
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_rSocket"));
}

void APlayerAvatar::DropWeapon()
{
	TArray<AActor*> attachedActors;
	GetAttachedActors(attachedActors, true);
	for (int i = 0; i < attachedActors.Num(); ++i)
	{
		attachedActors[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		attachedActors[i]->SetActorRotation(FQuat::Identity);
		AWeapon* weapon = Cast<AWeapon>(attachedActors[i]);
		if (weapon != nullptr)
		{
			weapon->Holder = nullptr;
		}
	}
}

void APlayerAvatar::Attack_RPC_Implementation()
{
	Attack_Broadcast_RPC();
}


void APlayerAvatar::DieProcess()
{
	ENetMode netMode = GetNetMode();
	if (netMode == ENetMode::NM_ListenServer)
	{
		DropWeapon();
	}
	
	if ((netMode == ENetMode::NM_ListenServer || netMode == ENetMode::NM_Client) && IsLocallyControlled())
	{
		OnPlayerIsKilledDelegate.Broadcast();
	}

	Super::DieProcess();
}
