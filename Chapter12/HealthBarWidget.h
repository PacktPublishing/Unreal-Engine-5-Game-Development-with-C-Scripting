#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

UCLASS()
class PANGAEA_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* HealthProgressBar;
};
