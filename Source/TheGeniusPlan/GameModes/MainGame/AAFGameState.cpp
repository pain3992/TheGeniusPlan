// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameState.h"
#include "TheGeniusPlan/PlayerState/AAFPlayerState.h"

AAAFGameState::AAAFGameState()
{
}

bool AAAFGameState::CheckPlayerState()
{
	for(auto PlayerState : GetAllPlayerStates())
	{
		AAAFPlayerState* Player = Cast<AAAFPlayerState>(PlayerState);
		if(Player)
		{
			if (Player->GetSelectedLand() == ESelectedLand::None)
			{
				AbundanceLand = 0;
				FamineLand = 0;
				return 0;
			}
			else if (Player->GetSelectedLand() == ESelectedLand::AbundanceLand)
			{
				AbundanceLand++;
			}
			else
			{
				FamineLand++;
			}
		}
	}

	return 1;
}

void AAAFGameState::ShowPlayerState()
{
	if(CheckPlayerState())
	{

	}
}
