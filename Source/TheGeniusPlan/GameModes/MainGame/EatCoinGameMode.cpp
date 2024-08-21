// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

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
    if (!PlayerCharacter)
    {
        return;
    }

    UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement();
    if (!MovementComponent)
    {
        return;
    }

    if (!bIsBoostActive)
    {
        // Store the original speed if not already boosted
        OriginalSpeed = MovementComponent->MaxWalkSpeed;

        // Apply the speed boost
        MovementComponent->MaxWalkSpeed *= SpeedMultiplier;

        // 부스터 습득 시 속도 확인용 로그 출력 (테스트 확인 후 지웁니다)
        if (GEngine)
        {
            FString SpeedText = FString::Printf(TEXT("Current Speed: %f"), MovementComponent->MaxWalkSpeed);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, SpeedText);
        }

        // Mark boost as active
        bIsBoostActive = true;
    }

    else
    {
        // 부스터 남은 시간 리셋 확인용 로그 출력 (테스트 확인 후 지웁니다)
        if (GEngine)
        {
            FString SpeedText = FString::Printf(TEXT("Boost Timer Reset. Current Speed: %f"), MovementComponent->MaxWalkSpeed);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, SpeedText);
        }
    }

    // Reset the boost duration timer
    GetWorld()->GetTimerManager().ClearTimer(BoostTimerHandle);
    GetWorld()->GetTimerManager().SetTimer(BoostTimerHandle, [this, MovementComponent]()
        {
            // 속도를 기본 속도로 리셋
            MovementComponent->MaxWalkSpeed = OriginalSpeed;
            bIsBoostActive = false;

            // 부스터 지속 시간이 지났을 때 속도 확인용 로그 출력 (테스트 확인 후 지웁니다)
            if (GEngine)
            {
                FString SpeedText = FString::Printf(TEXT("Speed Reset to Original: %f"), MovementComponent->MaxWalkSpeed);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, SpeedText);
            }

        }, BoostDuration, false);
}