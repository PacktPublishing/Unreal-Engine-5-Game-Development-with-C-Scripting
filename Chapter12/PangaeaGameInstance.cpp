
#include "PangaeaGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPangaeaGameInstance::StartTopdownListenServer()
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, "TopDownMap", true, "?listen");
}

void UPangaeaGameInstance::StartElvenRuinsListenServer()
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, "ElvenRuins", true, "?listen");
}

void UPangaeaGameInstance::JoinAsClient(FString IPAddress)
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, *IPAddress, true, "?join");
}


void UPangaeaGameInstance::LeaveGame()
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, "LobbyMap");
}