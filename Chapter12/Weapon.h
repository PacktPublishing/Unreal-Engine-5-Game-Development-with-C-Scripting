#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Weapon.generated.h"

UCLASS()
class PANGAEA_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class APangaeaCharacter* Holder = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon Params")
		float Strength = 10;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* _StaticMesh;

	UFUNCTION()
	void OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	virtual void Tick(float DeltaTime) override;
	bool IsWithinAttackRange(float AttackRange, AActor* Target);
};
