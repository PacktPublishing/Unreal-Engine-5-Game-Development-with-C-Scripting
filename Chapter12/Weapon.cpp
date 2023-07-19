#include "Weapon.h"
#include "PangaeaCharacter.h"
#include "PlayerAvatar.h"
#include "DefenseTower.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(_StaticMesh);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBeginOverlap);
}

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

	if (character == nullptr)
	{
		return;
	}
		
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
	else if (GetNetMode() == ENetMode::NM_ListenServer &&
		character != Holder &&
		IsWithinAttackRange(0.0f, OtherActor) &&
		character->CanBeDamaged() &&
		Holder->IsAttacking())
	{
		character->Hit(Holder->Strength);

		if (character->IsA(APlayerAvatar::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Hit PlayerAvatar"));
			UE_LOG(LogTemp, Log, TEXT("Hit PlayerAvatar"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Hit Enemy"));
			UE_LOG(LogTemp, Log, TEXT("Hit Enemy"));
		}
	}
}


bool AWeapon::IsWithinAttackRange(float AttackRange, AActor* Target)
{
	float distance = FVector::Distance(Target->GetActorLocation(), GetActorLocation());
	return (AttackRange <= 0.0f || distance <= AttackRange);
}
