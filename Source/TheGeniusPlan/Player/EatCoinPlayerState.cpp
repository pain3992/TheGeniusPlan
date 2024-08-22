// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Player/EatCoinPlayerState.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameState.h"
#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "GameFramework/HUD.h"
#include "Net/UnrealNetwork.h"


AEatCoinPlayerState::AEatCoinPlayerState()
{
    bIsBoostActive = false;
    BoostTimeLeft = 0.0f;
}

int32 AEatCoinPlayerState::GetCoinScore() const
{
    return CoinScore;
}

void AEatCoinPlayerState::StartBoostCountdown(float Duration)
{
    BoostTimeLeft = Duration;
    bIsBoostActive = true;

    // Start the countdown timer
    GetWorld()->GetTimerManager().SetTimer(
        BoostCountdownTimerHandle,
        this,
        &AEatCoinPlayerState::UpdateBoostCountdown,
        1.0f, // Update interval: 1 second
        true  // Looping
    );

    // Notify clients about the boost state
    OnRep_BoostTime();
}

void AEatCoinPlayerState::UpdateBoostCountdown()
{
    if (BoostTimeLeft > 0)
    {
        BoostTimeLeft -= 1.0f;

        if (BoostTimeLeft <= 0)
        {
            bIsBoostActive = false;
            GetWorld()->GetTimerManager().ClearTimer(BoostCountdownTimerHandle);
        }

        // Notify the client about the updated time
        OnRep_BoostTime();
    }
}

void AEatCoinPlayerState::OnRep_BoostTime()
{
    // 클라이언트에서 UI 업데이트 등의 작업을 수행
    if (APlayerController* PlayerController = GetPlayerController())
    {
        if (AEatCoinHUD* CoinHUD = PlayerController->GetHUD<AEatCoinHUD>())
        {
            if (UEatCoinWidget* EatCoinWidget = CoinHUD->GetEatCoinWidget())
            {
                EatCoinWidget->UpdateBoostTimer(); // UI 업데이트
            }
        }
    }
}

void AEatCoinPlayerState::AddCoinScore(int32 CoinAmount)
{
    // Retrieve the player's name
    FString CurrentPlayerName = GetPlayerName();

    // Log the information including the player name and the amount of score added
    UE_LOG(LogTemp, Warning, TEXT("%s에게 %d점을 추가했습니다. 현재 총 점수: %d"),
        *CurrentPlayerName, CoinAmount, static_cast<int32>(GetScore() + CoinAmount));


    CoinScore += CoinAmount;

    // Notify clients about the score change
    OnRep_CoinScore();
}

void AEatCoinPlayerState::OnRep_CoinScore() const
{
    if (GetWorld()->GetGameState<AEatCoinGameState>())
    {
        AEatCoinGameState* EatCoinGameState = GetWorld()->GetGameState<AEatCoinGameState>();
      //  EatCoinGameState->
            //OnRep_PlayerCoinScores();
    }
}


void AEatCoinPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AEatCoinPlayerState, BoostTimeLeft);
    DOREPLIFETIME(AEatCoinPlayerState, bIsBoostActive);
    DOREPLIFETIME(AEatCoinPlayerState, CoinScore);
}