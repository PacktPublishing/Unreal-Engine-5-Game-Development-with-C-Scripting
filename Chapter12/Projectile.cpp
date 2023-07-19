#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "PangaeaGameMode.h"
#include "PlayerAvatar.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(_MeshComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	_PangaeaGameMode = Cast<APangaeaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Reset();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetNetMode() == NM_Client)
	{
		return;
	}

	if (_LifeCountingDown > 0.0f)
	{
		FVector currentLocation = GetActorLocation();
		FVector vel = GetActorRotation().RotateVector(FVector::ForwardVector) * Speed * DeltaTime;
		FVector nextLocation = currentLocation + vel;
		SetActorLocation(nextLocation);

		//Ray cast check
		FHitResult hitResult;
		FCollisionObjectQueryParams objCollisionQueryParams;
		objCollisionQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

		if (GetWorld()->LineTraceSingleByObjectType(hitResult, currentLocation, nextLocation, objCollisionQueryParams))
		{
			auto playerAvatar = Cast<APlayerAvatar>(hitResult.GetActor());
			if (playerAvatar != nullptr)
			{
				playerAvatar->Hit(Damage);
				_PangaeaGameMode->RecycleFireball(this);

			}
		}

		_LifeCountingDown -= DeltaTime;
	}
	else
	{
		_PangaeaGameMode->RecycleFireball(this);
	}
}

void AProjectile::Reset()
{
	_LifeCountingDown = Lifespan;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}