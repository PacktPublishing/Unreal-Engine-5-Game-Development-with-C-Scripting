#include "PangaeaGameMode.h"
#include "PangaeaCharacter.h"
#include "PangaeaPlayerController.h"
#include "PangaeaGameState.h"
#include "UObject/ConstructorHelpers.h"


APangaeaGameMode::APangaeaGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APangaeaPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_PlayerAvatar"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	GameStateClass = APangaeaGameState::StaticClass();
}

APangaeaGameMode::~APangaeaGameMode()
{
	AProjectile* fireball;
	while (!_FireballPool.IsEmpty() && _FireballPool.Dequeue(fireball))
	{
		fireball->Destroy();
	}
	_FireballPool.Empty();
}

AProjectile* APangaeaGameMode::SpawnOrGetFireball(UClass* projectileClass)
{
	AProjectile* fireball = nullptr;

	if (_FireballPool.IsEmpty())
	{
		fireball = Cast<AProjectile>(GetWorld()->SpawnActor(projectileClass));
	}
	else
	{
		_FireballPool.Dequeue(fireball);
		fireball->Reset();
	}

	return fireball;
}

void APangaeaGameMode::RecycleFireball(AProjectile* projectile)
{
	if (projectile == nullptr)
	{
		return;
	}

	projectile->SetActorHiddenInGame(true);
	projectile->SetActorEnableCollision(false);
	projectile->SetActorTickEnabled(false);

	_FireballPool.Enqueue(projectile);
}