
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PangaeaGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerChangedDelegate, float, Timer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameWinLoseDelegate, bool, Win);

UCLASS()
class PANGAEA_API APangaeaGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(BlueprintAssignable, Category = "Pangaea")
		FOnTimerChangedDelegate OnTimerChangedDelegate;

	UFUNCTION(BlueprintCallable, Category = "Pangaea")
		void OnTimerChanged();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnTimerChanged, Category = "Pangaea")
		float Timer = 0;

	UPROPERTY(BlueprintAssignable, Category = "Pangaea")
		FOnGameWinLoseDelegate OnGameWinLoseDelegate;

	UFUNCTION(BlueprintCallable, Category = "Pangaea")
		void OnGameWin();


	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnGameWin, Category = "Pangaea")
		bool GameWin;

};
