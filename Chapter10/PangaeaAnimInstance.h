
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PangaeaAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Locomotion,
	Attack,
	Hit,
	Die
};


UCLASS()
class PANGAEA_API UPangaeaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PangaeaAnimInstance Params")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PangaeaAnimInstance Params")
		ECharacterState State;

	UFUNCTION(BlueprintCallable)
		void OnStateAnimationEnds();
};
