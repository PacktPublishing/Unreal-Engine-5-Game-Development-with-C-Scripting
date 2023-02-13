// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.generated.h"

UCLASS(Blueprintable)
class PANGAEA_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, Category = "Projectile Params")
		float Speed = 100.0f;		//the projectile's speed

	UPROPERTY(EditAnywhere, Category = "Projectile Params")
		float Lifespan = 5.0f;		//the projectile's lifespan

	UPROPERTY(EditAnywhere, Category = "Projectile Params")
		float Damage = 10.0f;		//the projectile's damage points

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Visual, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* _BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Visual, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* _MeshComponent;

	float _LifeCountingDown;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetBoxComponent() const { return _BoxComponent; }
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return _MeshComponent; }
};
