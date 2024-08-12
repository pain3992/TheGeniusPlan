// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFPlayerState.h"
#include "TheGeniusPlan/GameState/AAFGameState.h"
#include "Net/UnrealNetwork.h"

void AAAFPlayerState::CheckAllPlayerLand()
{
	AAAFGameState* GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());
	if(GameState)
	{
		GameState->CheckPlayerState();
	}
}

AAAFPlayerState::AAAFPlayerState()
{
	SelectedLand = ESelectedLand::None;
}

void AAAFPlayerState::ChangeLand(ESelectedLand Select)
{
	SelectedLand = Select;
}

ESelectedLand AAAFPlayerState::GetSelectedLand()
{
	return SelectedLand;
}

void AAAFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAAFPlayerState, SelectedLand);
}
