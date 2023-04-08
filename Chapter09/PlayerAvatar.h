// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PangaeaCharacter.h"
#include "Weapon.h"

#include "PlayerAvatar.generated.h"

UCLASS(Blueprintable)
class PANGAEA_API APlayerAvatar : public APangaeaCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerAvatar();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerAvatar")
	void AttachWeapon(AWeapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerAvatar")
	void DropWeapon();

	void Attack() override;	

	FORCEINLINE class UCameraComponent* GetCameraComponet() const { return _CameraComponent; }
	FORCEINLINE class USpringArmComponent* GetSringArmComponet() const { return _SpringArmComponent; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* _SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* _CameraComponent;

};
