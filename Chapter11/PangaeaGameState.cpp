#include "PangaeaGameState.h"
#include <Net/UnrealNetwork.h>

void APangaeaGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APangaeaGameState, Timer);
}

void APangaeaGameState::OnTimerChanged()
{
    OnTimerChangedDelegate.Broadcast(Timer);
}

void APangaeaGameState::OnGameWin()
{
    GameWin = true;
    OnGameWinLoseDelegate.Broadcast(true);
}


