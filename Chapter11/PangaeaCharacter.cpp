// Copyright Epic Games, Inc. All Rights Reserved.

#include "PangaeaCharacter.h"
#include "PangaeaAnimInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ProgressBar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include <Net/UnrealNetwork.h>


void APangaeaCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APangaeaCharacter, _HealthPoints);
}

APangaeaCharacter::APangaeaCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
}


void APangaeaCharacter::OnHealthPointsChanged()
{
    if (HealthBarWidget != nullptr)
    {
        float normalizedHealth = FMath::Clamp((float)_HealthPoints / HealthPoints, 0.0f, 1.0f);
        auto healthBar = Cast<UHealthBarWidget>(HealthBarWidget);
        healthBar->HealthProgressBar->SetPercent(normalizedHealth);
    }
    
    if (_AnimInstance != nullptr)
    {
        _AnimInstance->State = ECharacterState::Hit;
    }

    if (IsKilled())
    {
        PrimaryActorTick.bCanEverTick = false;
    }
}

void APangaeaCharacter::BeginPlay()
{
    Super::BeginPlay();

    auto components = GetComponents();

    _AnimInstance = Cast<UPangaeaAnimInstance>(GetMesh()->GetAnimInstance());
    _HealthPoints = HealthPoints;
}

void APangaeaCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    _AnimInstance->Speed = GetCharacterMovement()->Velocity.Size2D();

    if (_AttackCountingDown == AttackInterval)
    {
        _AnimInstance->State = ECharacterState::Attack;
    }

    if (_AttackCountingDown > 0.0f)
    {
        _AttackCountingDown -= DeltaSeconds;
    }
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

    if (GetNetMode() == ENetMode::NM_ListenServer && HasAuthority())
    {
        _HealthPoints -= damage;
        OnHealthPointsChanged();
    }
}

void APangaeaCharacter::DieProcess()
{
    PrimaryActorTick.bCanEverTick = false;
    Destroy();
    GEngine->ForceGarbageCollection(true);
}

void APangaeaCharacter::Attack_Broadcast_RPC_Implementation()
{
    Attack();
}
