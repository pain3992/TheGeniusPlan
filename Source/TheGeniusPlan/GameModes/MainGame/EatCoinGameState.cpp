#include "EatCoinGameState.h"
#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

AEatCoinGameState::AEatCoinGameState()
{
}

void AEatCoinGameState::OnRep_PlayingPlayers() const
{
    Super::OnRep_PlayingPlayers();

    // Additional logic for EatCoinHUD and EatCoinWidget
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AEatCoinHUD* CoinHUD = (*It)->GetHUD<AEatCoinHUD>())
        {
            if (UEatCoinWidget* EatCoinWidget = CoinHUD->GetEatCoinWidget())
            {
                EatCoinWidget->UpdateEatCoinPlayerList(PlayingPlayers);
            }
        }
    }
}

void AEatCoinGameState::ShowWidgetPlayerRanking_Implementation()
{
    // Call the base class implementation first to ensure the existing logic runs
    Super::ShowWidgetPlayerRanking_Implementation();

    // Additional logic for EatCoinHUD and EatCoinWidget
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AEatCoinHUD* CoinHUD = (*It)->GetHUD<AEatCoinHUD>())
        {
            if (UEatCoinWidget* EatCoinWidget = CoinHUD->GetEatCoinWidget())
            {
                for (AGeniusPlayerState* PlayerState : PlayingPlayers)
                {
                    if (PlayerState)
                    {
                        OnRep_PlayingPlayers();
                    }
                }
            }
        }
    }
}
