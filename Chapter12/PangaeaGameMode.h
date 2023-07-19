#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Projectile.h"

#include "PangaeaGameMode.generated.h"

UCLASS(minimalapi)
class APangaeaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APangaeaGameMode();
	~APangaeaGameMode();

	AProjectile* SpawnOrGetFireball(UClass* ProjectileClass);
	void RecycleFireball(AProjectile* projectile);

protected:

	TQueue<AProjectile*, EQueueMode::Spsc> _FireballPool;
};



