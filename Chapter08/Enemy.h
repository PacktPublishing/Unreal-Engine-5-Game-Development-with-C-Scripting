// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "Enemy.generated.h"

UCLASS()
class PANGAEA_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	int HealthPoints = 100;			//the character's max health points

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	float Strength = 5;			//the character's attack strength

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	float Armor = 1;				//the character's defense armor

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	float AttackRange = 200.0f;		//the character's attack range

	UPROPERTY(EditAnywhere, Category = "Enemy Params")
	float AttackInterval = 3.0f;	//the character's attack invertal

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int _HealthPoints;
	float _AttackCountingDown;
	APawn* _chasedTarget = nullptr;
	
	UClass* _WeaponClass;
	AWeapon* _Weapon;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy", meta = (DisplayName = "Get HP"))
	int GetHealthPoints();			//get current health points

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy")
	bool IsKilled();				//check if the character has been killed

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy")
	bool CanAttack();				//check if the character can attack

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy")
	void Chase(APawn* targetPawn);

	void Attack();
	void Hit(int damage);
	void DieProcess();				//process when the character is killed

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnSensingComponent* PawnSensingComponent;
};
