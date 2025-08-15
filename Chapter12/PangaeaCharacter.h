#pragma once

#include "CoreMinimal.h"
#include "HealthBarWidget.h"
#include "GameFramework/Character.h"

#include "PangaeaCharacter.generated.h"

UCLASS(Blueprintable)
class APangaeaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APangaeaCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, Category = "Pangaea Character Params")
		int HealthPoints = 100;			//the character's max health points

	UPROPERTY(EditAnywhere, Category = "Pangaea Character Params")
		float Strength = 5;			//the character's attack strength

	UPROPERTY(EditAnywhere, Category = "Pangaea Character Params")
		float Armor = 1;				//the character's defense armor

	UPROPERTY(EditAnywhere, Category = "Pangaea Character Params")
		float AttackRange = 200.0f;		//the character's attack range

	UPROPERTY(EditAnywhere, Category = "Pangaea Character Params")
		float AttackInterval = 3.0f;	//the character's attack invertval

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UUserWidget* HealthBarWidget;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Character", meta = (DisplayName = "Get HP"))
		int GetHealthPoints();			//get current health points

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Character")
		bool IsKilled();				//check if the character has been killed

	UFUNCTION(BlueprintCallable, Category = "Pangaea|Character")
		bool CanAttack();
	bool IsAttacking();

	virtual void Attack();
	virtual void Hit(int damage);
	virtual void DieProcess();

public:

	UFUNCTION(NetMultiCast, Reliable)
		void Attack_Broadcast_RPC();

protected:
	virtual void BeginPlay() override;

	class UPangaeaAnimInstance* _AnimInstance;

	float _AttackCountingDown;

	UPROPERTY(Replicatedusing = OnHealthPointsChanged)
		int _HealthPoints;

	UFUNCTION()
		void OnHealthPointsChanged();
};

