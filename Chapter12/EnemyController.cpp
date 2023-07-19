#include "EnemyController.h"
#include "Enemy.h"

void AEnemyController::MakeAttackDecision(APawn* targetPawn)
{
	auto enemy = Cast<AEnemy>(GetPawn());
	auto dist = FVector::Dist2D(targetPawn->GetActorLocation(), GetPawn()->GetTargetLocation());

	if (dist <= enemy->AttackRange && enemy->CanAttack())
	{
		StopMovement();
		enemy->Attack_Broadcast_RPC();
	}
}