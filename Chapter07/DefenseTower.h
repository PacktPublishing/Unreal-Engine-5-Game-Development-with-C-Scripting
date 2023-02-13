// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DefenseTower.generated.h"

UCLASS(Blueprintable)
class PANGAEA_API ADefenseTower : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADefenseTower();

	UPROPERTY(EditAnywhere, Category = "Tower Params")
		int HealthPoints = 100;			//the tower's max health points

	UPROPERTY(EditAnywhere, Category = "Tower Params")
		int ShellDefense = 2;			//the tower's shell defense value 

	UPROPERTY(EditAnywhere, Category = "Tower Params")
		float AttackRange = 15.0f;		//the tower's attack range

	UPROPERTY(EditAnywhere, Category = "Tower Params")
		float ReloadInterval = 1.0f;	//the tower's reload interval
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int _HealthPoints;				//the tower's current health points
	float _ReloadCountingDown;		//reload counting down

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* _BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* _MeshComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetBoxComponent() const { return _BoxComponent; }
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return _MeshComponent; }

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower", meta = (DisplayName = "GetHP"))
		int GetHealthPoints();			//get current life point

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower")
		bool IsDestroyed();				//check if the tower has been destroyed

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower")
		bool CanFire();					//check if the tower can fire

	void Fire();					//fire a project tile
	void Hit(int damage);			//process when the tower is hit
protected:
	void DestroyProcess();			//process when the tower is destroyed
};
