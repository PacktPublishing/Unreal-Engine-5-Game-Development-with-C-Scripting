// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatarAnimInstance.h"
#include "PlayerAvatar.h"

void UPlayerAvatarAnimInstance::OnStateAnimationEnds()
{
	if (State == EPlayerState::Attack)
	{
		State = EPlayerState::Locomotion;
	}
	else
	{
		auto ownerActor = this->GetOwningActor();
		auto playerAvatar = Cast<APlayerAvatar>(ownerActor);
	
		if (playerAvatar == nullptr)
		{
			UE_LOG(LogAnimation, Error, TEXT("The owner actor is not a PlayerAvatar!"));
			return;
		}

		if (State == EPlayerState::Hit)
		{
			if (playerAvatar->GetHealthPoints() > 0.0f)
			{
				State = EPlayerState::Locomotion;
			}
			else
			{
				State = EPlayerState::Die;
			}

		}
		else if (State == EPlayerState::Die)
		{
			//...
		}
	}
}