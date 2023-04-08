#pragma once

#include "CoreMinimal.h"
#include "PangaeaCharacter.h"
#include "Weapon.h"

#include "Enemy.generated.h"

UCLASS()
class PANGAEA_API AEnemy : public APangaeaCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

	APawn* _chasedTarget = nullptr;
	UClass* _WeaponClass;
	AWeapon* _Weapon;
	
public:	
	virtual void Tick(float DeltaTime) override;

	void Attack() override;
	void DieProcess() override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy")
	void Chase(APawn* targetPawn);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnSensingComponent* PawnSensingComponent;
};
