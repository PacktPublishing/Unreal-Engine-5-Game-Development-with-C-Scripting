// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "Enemy.h"

void UEnemyAnimInstance::OnStateAnimationEnds()
{
	if (State == EEnemyState::Attack)
	{
		State = EEnemyState::Locomotion;
	}
	else
	{
		auto enemy = Cast<AEnemy>(GetOwningActor());

		if (State == EEnemyState::Hit)
		{
			if (enemy->GetHealthPoints() > 0.0f)
			{
				State = EEnemyState::Locomotion;
			}
			else
			{
				State = EEnemyState::Die;
			}

		}
		else if (State == EEnemyState::Die)
		{
			enemy->DieProcess();
		}
	}
}