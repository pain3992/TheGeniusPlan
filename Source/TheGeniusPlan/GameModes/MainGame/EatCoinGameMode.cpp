// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "TheGeniusPlan/Player/EatCoinPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameState.h"

AEatCoinGameMode::AEatCoinGameMode()
{
	CountdownTimeInSeconds = 180;
}

void AEatCoinGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void AEatCoinGameMode::ApplySpeedBoost(ACharacter* PlayerCharacter)
{
    if (!PlayerCharacter) return;

    AEatCoinPlayerState* PlayerState = PlayerCharacter->GetPlayerState<AEatCoinPlayerState>();
    if (PlayerState)
    {
        UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement();
        if (MovementComponent)
        {
            if (!bIsBoostActive)
            {
                // 부스트 활성화 되지 않은 상태일 경우 원래 속도 저장
                OriginalSpeed = MovementComponent->MaxWalkSpeed;

                // 부스트 속도 적용(2배)
                MovementComponent->MaxWalkSpeed *= SpeedMultiplier;
                bIsBoostActive = true;

                // 부스트 카운트다운 시작(또는 재시작)
                PlayerState->StartBoostCountdown(BoostDuration);
            }
            else
            {
                GetWorld()->GetTimerManager().ClearTimer(BoostTimerHandle);
            }

            // 부스터 타이머 시작(또는 재시작)
            GetWorld()->GetTimerManager().SetTimer(
                BoostTimerHandle,
                [this, PlayerCharacter]()
                {
                    UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement();
                    if (MovementComponent)
                    {
                        // Reset the speed to the original value
                        MovementComponent->MaxWalkSpeed = OriginalSpeed;

                        // Log output (for testing)
                        if (GEngine)
                        {
                            FString SpeedText = FString::Printf(TEXT("Speed Reset to Original: %f"), MovementComponent->MaxWalkSpeed);
                            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, SpeedText);
                        }
                    }
                    bIsBoostActive = false;

                    // 부스터 효과가 끝났음을 PlayerState에 알림
                    if (PlayerCharacter)
                    {
                        AEatCoinPlayerState* PlayerState = PlayerCharacter->GetPlayerState<AEatCoinPlayerState>();
                        if (PlayerState)
                        {
                            PlayerState->BoostTimeLeft = 0;
                            PlayerState->bIsBoostActive = false;
                        }
                    }
                },
                BoostDuration,
                false
            );

            // 새로운 부스트 지속시간을 PlayerState에 반영
            PlayerState->BoostTimeLeft = BoostDuration;
            PlayerState->bIsBoostActive = true;
        }
    }
}

void AEatCoinGameMode::AddCoinScoreRule(APlayerState* PlayerState, int32 ScoreAmount)
{
    AEatCoinPlayerState* EatCoinPlayerState = Cast<AEatCoinPlayerState>(PlayerState);
    {
        if (EatCoinPlayerState)
        {
            EatCoinPlayerState->AddCoinScore(ScoreAmount);

            if (AEatCoinGameState* EatCoinGameState = GetGameState <AEatCoinGameState>())
            {
                EatCoinGameState->ShowWidgetCoinRanking();
            }
        }
    }
}
