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
#include "TheGeniusPlan/Widget/MainGame/EatCoinEndWidget.h"
#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "TheGeniusPlan/Player/EatCoinPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameState.h"
#include "TheGeniusPlan/Player/EatCoinPlayerController.h"

AEatCoinGameMode::AEatCoinGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C'"));
    if (PlayerPawnBPClass.Succeeded())
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
    
    HUDClass = AEatCoinHUD::StaticClass();
    PlayerControllerClass = AEatCoinPlayerController::StaticClass();
    GameStateClass = AEatCoinGameState::StaticClass();
    PlayerStateClass = AEatCoinPlayerState::StaticClass();

    // 총 라운드
    TotalRound = 3;

    // 라운드 시간
	CountdownTimeInSeconds = 180;

    // EatCoin 게임 시작까지 남은 시간
    ECGameStartCountdownTimeInSeconds = 10;
}

void AEatCoinGameMode::BeginPlay()
{
  //  SetECGameStartCountdownRule();
    HandleGameStart();
}

void AEatCoinGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (AEatCoinGameState* EatCoinGameState = GetGameState<AEatCoinGameState>())
    {
        // 플레이어가 게임에 들어올 때, GameState의 플레이어 점수 목록을 업데이트합니다.
        EatCoinGameState->UpdatePlayerCoinScores();

        // 초기 상태를 UI에 반영할 수 있도록 모든 클라이언트에 UI 업데이트를 요청할 수 있습니다.
        EatCoinGameState->OnRep_PlayerCoinScores();
    }
}

void AEatCoinGameMode::HandleGameStart()
{
    Super::HandleGameStart();

    SetECGameStartCountdownRule();
}

void AEatCoinGameMode::TransitionToNextRound()
{
    if (CurrentRound < TotalRound)
    {
        CurrentRound++;
        UE_LOG(LogTemp, Log, TEXT("라운드 %d 시작!"), CurrentRound);

        // 라운드가 시작되도록 필요한 초기화 로직 추가 가능
      //  HandleGameStart();  // 새로운 라운드를 시작합니다.
    }
}

void AEatCoinGameMode::HandleRoundEnd()
{
    Super::HandleRoundEnd();

    if (CurrentRound < TotalRound)
    {
        UE_LOG(LogTemp, Log, TEXT("라운드 %d 종료, 다음 라운드 준비 중..."), CurrentRound);

        // 10초 후에 다음 라운드(TransitionToNextRound) 호출
        GetWorld()->GetTimerManager().SetTimer(RoundTransitionTimerHandle, this, &AEatCoinGameMode::TransitionToNextRound, 10.0f, false);

        // 10초 후에 ECGameStartCountdown을 시작합니다.
        GetWorld()->GetTimerManager().SetTimer(ECGameCountdownTimerHandle, this, &AEatCoinGameMode::SetECGameStartCountdownRule, 10.0f, false);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("모든 라운드 종료, 게임 종료!"));
        for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
        {
            APlayerController* PlayerController = It->Get();
            if (PlayerController)
            {
                AEatCoinHUD* EatCoinHUD = Cast<AEatCoinHUD>(PlayerController->GetHUD());
                if (EatCoinHUD && EatCoinHUD->GetEatCoinEndWidget())
                {
                    UE_LOG(LogTemp, Log, TEXT("게임 종료 위젯 호출"));
                    EatCoinHUD->GetEatCoinEndWidget()->SetVisibility(ESlateVisibility::Visible);
                }
            }
        }

        // 게임 종료 처리
        // 필요에 따라 게임 종료 후 로직 추가 (예: 게임 메인 메뉴로 돌아가기, 서버 종료 등)
    }
}



void AEatCoinGameMode::ApplySpeedBoost(ACharacter* PlayerCharacter)
{
    if (!PlayerCharacter) return;

    AEatCoinPlayerState* PlayerState = PlayerCharacter->GetPlayerState<AEatCoinPlayerState>();
    if (PlayerState && PlayerState->bIsBoostActive == false) // PlayerState에서 부스트 활성화 여부를 확인
    {
        UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement();
        if (MovementComponent)
        {
            // 기존 속도를 저장하고 부스트 속도 적용
            PlayerState->OriginalSpeed = MovementComponent->MaxWalkSpeed;
            MovementComponent->MaxWalkSpeed *= SpeedMultiplier;

            // 부스트 상태를 활성화하고 타이머 시작
            PlayerState->bIsBoostActive = true;
            PlayerState->StartBoostCountdown(BoostDuration);
        }
    }
    else if (PlayerState && PlayerState->bIsBoostActive) // 이미 부스트가 활성화된 상태일 때
    {
        // 기존 타이머를 연장하여 지속 시간을 리셋
        PlayerState->StartBoostCountdown(BoostDuration);
    }
}

void AEatCoinGameMode::AddCoinScoreRule(APlayerState* PlayerState, int32 ScoreAmount)
{
    AEatCoinPlayerState* EatCoinPlayerState = Cast<AEatCoinPlayerState>(PlayerState);
    if (EatCoinPlayerState)
    {
        EatCoinPlayerState->AddCoinScore(ScoreAmount);

        if (HasAuthority())
        {
            if (AEatCoinGameState* EatCoinGameState = GetGameState<AEatCoinGameState>())
            {
                EatCoinGameState->UpdatePlayerCoinScores();
            }
        }
    }
}

void AEatCoinGameMode::SetECGameStartCountdownRule()
{
    if (AEatCoinGameState* EatCoinGameState = GetGameState<AEatCoinGameState>())
    {
        EatCoinGameState->StartECGameCount(ECGameStartCountdownTimeInSeconds);
    }
}
