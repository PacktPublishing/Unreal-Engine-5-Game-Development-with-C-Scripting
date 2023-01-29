// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerAvatar.generated.h"

UCLASS(Blueprintable)
class PANGAEA_API APlayerAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerAvatar();

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
		int HealthPoints = 500;			//the character's max health points

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
		float Strength = 10;			//the character's attack strength

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
		float Armer = 3;				//the character's defense armer

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
		float AttackRange = 6.0f;		//the character's attack range

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
		float AttackInterval = 1.2f;	//the character's attack invertal
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int _HealthPoints;
	float _AttackCountingDown;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerCharacter", meta = (DisplayName = "Get HP"))
		int GetHealthPoints();			//get current health points

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerCharacter")
		bool IsKilled();				//check if the character has been killed

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerCharacter")
		bool CanAttack();				//check if the character can attack

	void Attack();					//attack
	void Hit(int damage);			//process when the character is hit

	FORCEINLINE class UCameraComponent* GetCameraComponet() const { return _cameraComponent; }
	FORCEINLINE class USpringArmComponent* GetSringArmComponet() const { return _springArmComponent; }

protected:
	void DieProcess();				//process when the character is killed

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* _springArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* _cameraComponent;

};
