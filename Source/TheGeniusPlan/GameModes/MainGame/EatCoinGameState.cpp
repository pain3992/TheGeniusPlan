#include "EatCoinGameState.h"
#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinMenualWidget.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinEndWidget.h"


AEatCoinGameState::AEatCoinGameState()
{
}

TArray<AEatCoinPlayerState*> AEatCoinGameState::GetAllPlayerCoinScores() const
{
    return PlayerCoinScores;
}

void AEatCoinGameState::UpdatePlayerCoinScores()
{
    PlayerCoinScores.Empty();

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PlayerController = It->Get();
        if (PlayerController)
        {
            AEatCoinPlayerState* PlayerState = PlayerController->GetPlayerState<AEatCoinPlayerState>();
            if (PlayerState)
            {
                PlayerCoinScores.Add(PlayerState);
            }
        }
    }

    // Notify all clients about the updated player scores
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

void AEatCoinGameState::CountdownFinished()
{
    Super::CountdownFinished();

    Multicast_OnCountdownFinished();
}

void AEatCoinGameState::Multicast_OnCountdownFinished_Implementation()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AEatCoinHUD* EatCoinHUD = (*It)->GetHUD<AEatCoinHUD>())
        {
            EatCoinHUD->ShowEatCoinEndWidget();
        }
    }
}

void AEatCoinGameState::StartECGameCount(int32 InitialCountdownTime)
{
    if (HasAuthority())
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("StartECCountdown"));
        ECGameCountdownTime = InitialCountdownTime;
        OnRep_ECGameCountdownTime();

        GetWorld()->GetTimerManager().SetTimer(ECGameCountdownTimerHandle, this, &AEatCoinGameState::UpdateECGameCount, 1.0f, true);
    }
}

void AEatCoinGameState::UpdateECGameCount()
{
    if (ECGameCountdownTime > 0)
    {
        ECGameCountdownTime--;
        OnRep_ECGameCountdownTime();
    }
    else
    {
        ECGameCountdownFinished();
    }
}

void AEatCoinGameState::OnRep_ECGameCountdownTime() const
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AEatCoinHUD* EatCoinHUD = (*It)->GetHUD<AEatCoinHUD>())
        {
            if (UEatCoinMenualWidget* ECMenualWidget = EatCoinHUD->GetEatCoinMenualWidget())
            {
                ECMenualWidget->UpdateStartEatCoinCountdownDisplay(ECGameCountdownTime);
            }
        }
    }
}

void AEatCoinGameState::ECGameCountdownFinished()
{
    GetWorld()->GetTimerManager().ClearTimer(ECGameCountdownTimerHandle);

    Multicast_OnECGameCountdownFinished();
}

void AEatCoinGameState::Multicast_OnECGameCountdownFinished_Implementation()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AEatCoinHUD* EatCoinHUD = (*It)->GetHUD<AEatCoinHUD>())
        {
            EatCoinHUD->CollapsedECMenualWidget();
            EatCoinHUD->ShowGameStartWidget();
        }
    }
    if (HasAuthority())
    {
        if (AEatCoinGameMode* EatCoinGameMode = GetWorld()->GetAuthGameMode<AEatCoinGameMode>())
        {
            EatCoinGameMode->SetCountdownRule();
        }
    }
}


void AEatCoinGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AEatCoinGameState, PlayerCoinScores);
    DOREPLIFETIME(AEatCoinGameState, ECGameCountdownTime);
}