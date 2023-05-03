// Fill out your copyright notice in the Description page of Project Settings.


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

// Called every frame
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
				//Destroy();
				_PangaeaGameMode->RecycleFireball(this);
				
			}
		}

		//Reduce time
		_LifeCountingDown -= DeltaTime;
	}
	else
	{
		//Destroy()
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