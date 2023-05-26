#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PangaeaGameInstance.generated.h"


UCLASS()
class PANGAEA_API UPangaeaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Pangaea")
	void StartListenServer();

	UFUNCTION(BlueprintCallable, Category = "Pangaea")
	void JoinAsClient(FString IPAddress);

	UFUNCTION(BlueprintCallable, Category = "Pangaea")
	void LeaveGame();

};
