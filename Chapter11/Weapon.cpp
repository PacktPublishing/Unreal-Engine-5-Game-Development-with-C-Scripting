// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "PangaeaCharacter.h"
#include "PlayerAvatar.h"
#include "DefenseTower.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(_StaticMesh);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBeginOverlap);
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Holder == nullptr)
	{
		FQuat rotQuat = FQuat(FRotator(0.0f, 300.0f * DeltaTime, 0.0f));
		AddActorLocalRotation(rotQuat);
	}
}


void AWeapon::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, TEXT("Weapon overlapped"));
	//UE_LOG(LogTemp, Log, TEXT("Weapon overlapped"));

	auto character = Cast<APangaeaCharacter>(OtherActor);

	if (character != nullptr)
	{
		if (Holder == nullptr)
		{
			auto playerAvatar = Cast<APlayerAvatar>(character);

			if (playerAvatar != nullptr)
			{
				Holder = character;
				playerAvatar->DropWeapon();
				playerAvatar->AttachWeapon(this);
			}
		}
		else if(character != Holder &&
				IsWithinAttackRange(0.0f, OtherActor) &&
				character->CanBeDamaged() &&
				Holder->IsAttacking())
		{
			character->Hit(Holder->Strength);
	
			if (character->IsA(APlayerAvatar::StaticClass()))
			{
				GEngine->AddOnScreenDebugMessage(- 1, 1.0f, FColor::Red, TEXT("Hit PlayerAvatar"));
				UE_LOG(LogTemp, Log, TEXT("Hit PlayerAvatar"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Hit Enemy"));
				UE_LOG(LogTemp, Log, TEXT("Hit Enemy"));
			}
		}
	}
	else if(Holder != nullptr && Holder->IsA(APangaeaCharacter::StaticClass()) && Holder->IsAttacking())
	{
		auto tower = Cast<ADefenseTower>(OtherActor);

		if (tower != nullptr && tower->CanBeDamaged() && IsWithinAttackRange(0.0f, tower))
		{
			tower->Hit(Strength);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Hit Tower"));
		}
	}
}

bool AWeapon::IsWithinAttackRange(float AttackRange, AActor* Target)
{
	return (AttackRange <= 0.0f || FVector::Distance(Target->GetActorLocation(), GetActorLocation()) <= AttackRange);
}
