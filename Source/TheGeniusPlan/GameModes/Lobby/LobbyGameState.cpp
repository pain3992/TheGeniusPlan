// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameState.h"
#include "Net/UnrealNetwork.h"
#include "TheGeniusPlan/Player/GameLobbyPlayerController.h"

void ALobbyGameState::IncrasePlayerCount()
{
}

ALobbyGameState::ALobbyGameState()
{
}

void ALobbyGameState::OnReq_ChangeConunt()
{
	if(PlayerCountDispatcher.IsBound())
	{
		PlayerCountDispatcher.Broadcast(PlayerCount);
	}
}

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameState, PlayerCount);
}

void ALobbyGameState::ChangePlayerCount(int32 NewNumber)
{
	PlayerCount = NewNumber;

	AGameLobbyPlayerController* PlayerController = Cast<AGameLobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->ChangePlayerCount(PlayerCount);
}
