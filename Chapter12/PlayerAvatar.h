#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PangaeaCharacter.h"
#include "Weapon.h"

#include "PlayerAvatar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerIsKilledDelegate);

UCLASS(Blueprintable)
class PANGAEA_API APlayerAvatar : public APangaeaCharacter
{
	GENERATED_BODY()

public:
	APlayerAvatar();


protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerAvatar")
		void AttachWeapon(AWeapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerAvatar")
		void DropWeapon();

	FORCEINLINE class UCameraComponent* GetCameraComponet() const { return _CameraComponent; }
	FORCEINLINE class USpringArmComponent* GetSringArmComponet() const { return _SpringArmComponent; }

	UFUNCTION(Server, Reliable)
		void Attack_RPC();

	UPROPERTY(BlueprintAssignable, Category = "Pangaea|PlayerAvatar")
	FOnPlayerIsKilledDelegate OnPlayerIsKilledDelegate;

	void DieProcess() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* _SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* _CameraComponent;

};
