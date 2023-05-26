#include "DefenseTower.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerAvatar.h"
#include "Projectile.h"
#include "PangaeaGameMode.h"
#include "PangaeaGameState.h"
#include <Net/UnrealNetwork.h>

void ADefenseTower::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADefenseTower, _HealthPoints);
}

ADefenseTower::ADefenseTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(_SphereComponent);
	_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefenseTower::OnBeginOverlap);
	_SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADefenseTower::OnEndOverlap);

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_MeshComponent->SetupAttachment(_SphereComponent);

	static ConstructorHelpers::FObjectFinder<UBlueprint> blueprint_finder(TEXT("Blueprint'/Game/TopDown/Blueprints/BP_Fireball.BP_Fireball'"));
	_FireballClass = (UClass*)blueprint_finder.Object->GeneratedClass;
}

void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();

	_SphereComponent->SetSphereRadius(AttackRange);
	SetActorTickInterval(ReloadInterval);
	_PangaeaGameMode = Cast<APangaeaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_Target != nullptr &&  GetNetMode() != NM_Client)
	{
		Fire();
	}
}

int ADefenseTower::GetHealthPoints()
{
	return _HealthPoints;
}

bool ADefenseTower::IsDestroyed()
{
	return (_HealthPoints > 0.0f);
}

bool ADefenseTower::CanFire()
{
	return (_ReloadCountingDown <= 0.0f);
}

void ADefenseTower::Fire()
{
	//auto fireball = Cast<AProjectile>(GetWorld()->SpawnActor(_FireballClass));
	auto fireball = _PangaeaGameMode->SpawnOrGetFireball(_FireballClass);

	FVector startLocation = GetActorLocation();
	startLocation.Z += 100.0f;
	FVector targetLocation = _Target->GetActorLocation();
	targetLocation.Z = startLocation.Z;
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(startLocation, targetLocation);
	fireball->SetActorLocation(startLocation);
	fireball->SetActorRotation(rotation);
}

void ADefenseTower::OnHealthPointsChanged()
{
	if (HealthBarWidget != nullptr)
	{
		float normalizedHealth = FMath::Clamp((float)_HealthPoints / HealthPoints, 0.0f, 1.0f);
		auto healthBar = Cast<UHealthBarWidget>(HealthBarWidget);
		healthBar->HealthProgressBar->SetPercent(normalizedHealth);
	}

	if (IsKilled())
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}

void ADefenseTower::Hit(int damage)
{
	if (IsKilled())
	{
		return;
	}

	if (GetNetMode() == ENetMode::NM_ListenServer && HasAuthority())
	{
		_HealthPoints -= damage;
		OnHealthPointsChanged();
		
		if (_HealthPoints <= 0)
		{
			if (IsBase)
			{
				APangaeaGameState* gameState = Cast<APangaeaGameState>(UGameplayStatics::GetGameState(GetWorld()));
				gameState->OnGameWin();
			}
			else
			{
				Destroy();
			}
		}
	}
}

bool ADefenseTower::IsKilled()
{
	return (HealthPoints <= 0.0f);
}

void ADefenseTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APlayerAvatar* player = Cast<APlayerAvatar>(OtherActor);

	if (player)
	{
		_Target = player;
	}
}


void ADefenseTower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex)
{
	if (_Target != nullptr && OtherActor == _Target)
	{
		_Target = nullptr;
	}
}


