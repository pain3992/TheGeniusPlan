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

void AEatCoinPlayerState::SetCoinScore(int32 NewScore)
{
    CoinScore = NewScore;
}

void AEatCoinPlayerState::StartBoostCountdown(float Duration)
{
    BoostTimeLeft = Duration;

    // 기존 타이머를 초기화하고 새 타이머 시작
    GetWorld()->GetTimerManager().ClearTimer(BoostCountdownTimerHandle);
    GetWorld()->GetTimerManager().SetTimer(
        BoostCountdownTimerHandle,
        this,
        &AEatCoinPlayerState::UpdateBoostCountdown,
        1.0f, // 1초마다 업데이트
        true  // 반복 실행
    );

    // 클라이언트에게 부스트 상태 알림
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

            // 부스트 시간 종료 후 속도 원래대로 복원
            ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawn());
            if (PlayerCharacter)
            {
                UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement();
                if (MovementComponent)
                {
                    MovementComponent->MaxWalkSpeed = OriginalSpeed;
                }
            }
        }

        // 클라이언트에게 남은 시간 알림
        OnRep_BoostTime();
    }
}

void AEatCoinPlayerState::OnRep_BoostTime()
{
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
    SetCoinScore(GetCoinScore() + CoinAmount);
}

void AEatCoinPlayerState::OnRep_CoinScore() const
{
    UE_LOG(LogTemp, Warning, TEXT("CoinScore updated: %d"), CoinScore);
    UE_LOG(LogTemp, Warning, TEXT("왜 작동하지?"));

    if (GetWorld()->GetGameState<AEatCoinGameState>())
    {
        AEatCoinGameState* EatCoinGameState = GetWorld()->GetGameState<AEatCoinGameState>();
        EatCoinGameState->OnRep_PlayerCoinScores();
    }
}


void AEatCoinPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AEatCoinPlayerState, BoostTimeLeft);
    DOREPLIFETIME(AEatCoinPlayerState, bIsBoostActive);
    DOREPLIFETIME(AEatCoinPlayerState, CoinScore);
}