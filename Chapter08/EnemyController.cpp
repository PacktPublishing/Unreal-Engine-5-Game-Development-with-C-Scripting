// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "Enemy.h"

void AEnemyController::MakeAttackDecision(APawn* targetPawn)
{
	auto controlledCharacter = Cast<AEnemy>(GetPawn());
	auto dist = FVector::Dist2D(targetPawn->GetActorLocation(), GetPawn()->GetTargetLocation());
	//UE_LOG(LogTemp, Warning, TEXT("Distance=%d"), dist);
	if (dist <= controlledCharacter->AttackRange && controlledCharacter->CanAttack())
	{
		controlledCharacter->Attack();
	}
}