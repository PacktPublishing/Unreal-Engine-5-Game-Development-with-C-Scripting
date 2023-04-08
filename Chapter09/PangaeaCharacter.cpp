// Copyright Epic Games, Inc. All Rights Reserved.

#include "PangaeaCharacter.h"
#include "PangaeaAnimInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

APangaeaCharacter::APangaeaCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APangaeaCharacter::BeginPlay()
{
    Super::BeginPlay();

    _AnimInstance = Cast<UPangaeaAnimInstance>(GetMesh()->GetAnimInstance());
    _HealthPoints = HealthPoints;
}

void APangaeaCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

int APangaeaCharacter::GetHealthPoints()
{
    return _HealthPoints;
}

bool APangaeaCharacter::IsKilled()
{
    return (_HealthPoints <= 0.0f);
}

bool APangaeaCharacter::CanAttack()
{
    return (_AttackCountingDown <= 0.0f && _AnimInstance->State == ECharacterState::Locomotion);
}

bool APangaeaCharacter::IsAttacking()
{
    return (_AnimInstance->State == ECharacterState::Attack);
}

void APangaeaCharacter::Attack()
{
    _AttackCountingDown = AttackInterval;
}

void APangaeaCharacter::Hit(int damage)
{
    if (IsKilled())
    {
        return;
    }

    _HealthPoints -= damage;

    
    _AnimInstance->State = ECharacterState::Hit;

    if (IsKilled())
    {
        PrimaryActorTick.bCanEverTick = false;
    }
}

void APangaeaCharacter::DieProcess()
{
    PrimaryActorTick.bCanEverTick = false;
    Destroy();
    GEngine->ForceGarbageCollection(true);
}