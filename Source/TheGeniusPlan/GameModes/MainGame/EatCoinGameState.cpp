#include "EatCoinGameState.h"
#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


AEatCoinGameState::AEatCoinGameState()
{
}

//void AEatCoinGameState::OnRep_PlayingPlayers() const
//{
//    Super::OnRep_PlayingPlayers();
//
//    // Additional logic for EatCoinHUD and EatCoinWidget
//    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//    {
//        if (AEatCoinHUD* CoinHUD = (*It)->GetHUD<AEatCoinHUD>())
//        {
//            if (UEatCoinWidget* EatCoinWidget = CoinHUD->GetEatCoinWidget())
//            {
//                EatCoinWidget->UpdateEatCoinPlayerList(PlayingPlayers);
//            }
//        }
//    }
//}

//void AEatCoinGameState::ShowWidgetPlayerRanking_Implementation()
//{
//    // Call the base class implementation first to ensure the existing logic runs
//    Super::ShowWidgetPlayerRanking_Implementation();
//
//    // Additional logic for EatCoinHUD and EatCoinWidget
//   /* for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//    {
//        if (AEatCoinHUD* CoinHUD = (*It)->GetHUD<AEatCoinHUD>())
//        {
//            if (UEatCoinWidget* EatCoinWidget = CoinHUD->GetEatCoinWidget())
//            {
//                for (AGeniusPlayerState* PlayerState : PlayingPlayers)
//                {
//                    if (PlayerState)
//                    {
//                        OnRep_PlayingPlayers();
//                    }
//                }
//            }
//        }
//    }*/
//
//    // Additional logic for EatCoinHUD and EatCoinWidget
//    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//    {
//        AEatCoinHUD* CoinHUD = (*It)->GetHUD<AEatCoinHUD>();
//        if (IsValid(CoinHUD) == false)
//            continue;
//
//        UEatCoinWidget * EatCoinWidget = CoinHUD->GetEatCoinWidget();
//        if (IsValid(EatCoinWidget) == false)
//            continue;
//
//        for (AGeniusPlayerState* PlayerState : PlayingPlayers)
//        {
//            if (PlayerState)
//            {
//                OnRep_PlayingPlayers();
//            }
//        }
//    }
//}

TArray<AEatCoinPlayerState*> AEatCoinGameState::GetAllPlayerCoinScores() const
{
    return PlayerCoinScores;
}

void AEatCoinGameState::UpdatePlayerCoinScores()
{
    PlayerCoinScores.Empty(); // 기존 목록을 비웁니다.

    // 모든 플레이어를 순회하여 점수를 가져옵니다.
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        TWeakObjectPtr<APlayerController> WeakPlayerController = *It;
        APlayerController* PlayerController = WeakPlayerController.Get(); // Get() 메서드를 사용

        if (PlayerController)
        {
            AEatCoinPlayerState* PlayerState = PlayerController->GetPlayerState<AEatCoinPlayerState>();
            if (PlayerState)
            {
                PlayerCoinScores.Add(PlayerState);
            }
        }
    }

    // UI 업데이트
    OnRep_PlayerCoinScores();
}


void AEatCoinGameState::OnRep_PlayerCoinScores() const
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AEatCoinHUD* CoinHUD = (*It)->GetHUD<AEatCoinHUD>())
        {
            if (UEatCoinWidget* EatCoinWidget = CoinHUD->GetEatCoinWidget())
            {
                EatCoinWidget->UpdateEatCoinPlayerList(PlayerCoinScores);
            }
        }
    }
}

void AEatCoinGameState::ShowWidgetCoinRanking_Implementation()
{
    if (PlayerCoinScores.Num() > 0)
    {
        // Get the first player controller
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

        if (AEatCoinHUD* CoinHUD = PlayerController ? PlayerController->GetHUD<AEatCoinHUD>() : nullptr)
        {
            if (UEatCoinWidget* EatCoinWidget = CoinHUD->GetEatCoinWidget())
            {
                EatCoinWidget->UpdateEatCoinPlayerList(PlayerCoinScores);
            }
        }
    }
}


void AEatCoinGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AEatCoinGameState, PlayerCoinScores);

}