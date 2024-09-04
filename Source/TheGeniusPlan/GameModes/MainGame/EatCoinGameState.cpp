#include "EatCoinGameState.h"
#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinMenualWidget.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinEndWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"
#include "TheGeniusPlan/Actor/EatCoinDoor.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "GameFramework/PlayerStart.h"
#include "TheGeniusPlan/GameModes/GeniusGameInstance.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"

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

    // 마지막 라운드인지 확인
    if (AEatCoinGameMode* EatCoinGameMode = GetWorld()->GetAuthGameMode<AEatCoinGameMode>())
    {
        if (EatCoinGameMode->GetCurrentRound() == EatCoinGameMode->GetTotalRound())
        {
            AwardTopPlayers();
        }
    }

    Multicast_OnCountdownFinished();
}


void AEatCoinGameState::Multicast_OnCountdownFinished_Implementation()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PlayerController = Cast<APlayerController>(*It);
        if (PlayerController)
        {
            ATheGeniusPlanCharacter* TheGeniusPlanCharacter = Cast<ATheGeniusPlanCharacter>(PlayerController->GetPawn());
            if (TheGeniusPlanCharacter)
            {
                // 캐릭터의 이동 컴포넌트 비활성화
                if (UCharacterMovementComponent* MoveComp = TheGeniusPlanCharacter->GetCharacterMovement())
                {
                    MoveComp->DisableMovement();
                }
            }

            if (AEatCoinHUD* EatCoinHUD = PlayerController->GetHUD<AEatCoinHUD>())
            {
                EatCoinHUD->ShowEatCoinEndWidget();

                // 리스트뷰를 화면 중앙으로 이동
                if (UEatCoinWidget* EatCoinWidget = EatCoinHUD->GetEatCoinWidget())
                {
                    EatCoinWidget->MoveListViewToCenter();
                }
            }
        }
    }
}

void AEatCoinGameState::StartECGameCount(int32 InitialCountdownTime)
{
    if (HasAuthority())
    {
        ECGameCountdownTime = InitialCountdownTime;
        OnRep_ECGameCountdownTime();

        GetWorld()->GetTimerManager().SetTimer(ECGameCountdownTimerHandle, this, &AEatCoinGameState::UpdateECGameCount, 1.0f, true);

        OnRep_MovePlayersToStart();
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
    // 플레이어 컨트롤러를 순회하며 플레이어를 PlayerStart 위치로 이동
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PlayerController = Cast<APlayerController>(*It);
        if (PlayerController)
        {
            ATheGeniusPlanCharacter* TheGeniusPlanCharacter = Cast<ATheGeniusPlanCharacter>(PlayerController->GetPawn());
            if (TheGeniusPlanCharacter)
            {
                // 캐릭터의 이동 컴포넌트를 다시 활성화
                if (UCharacterMovementComponent* MoveComp = TheGeniusPlanCharacter->GetCharacterMovement())
                {
                    MoveComp->SetMovementMode(MOVE_Walking); // 기본 이동 모드로 설정
                }
            }

            if (AEatCoinHUD* EatCoinHUD = PlayerController->GetHUD<AEatCoinHUD>())
            {
                EatCoinHUD->ShowECMenualWidget();
                EatCoinHUD->CollapsedECEndWidget();

                if (UEatCoinMenualWidget* ECMenualWidget = EatCoinHUD->GetEatCoinMenualWidget())
                {
                    ECMenualWidget->UpdateStartEatCoinCountdownDisplay(ECGameCountdownTime);
                }
                if (UEatCoinWidget* ECWidget = EatCoinHUD->GetEatCoinWidget())
                {
                    ECWidget->MoveListViewToOriginalPosition();
                }
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

    // 문을 찾고 열기 시작
    for (TActorIterator<AEatCoinDoor> It(GetWorld()); It; ++It)
    {
        (*It)->StartOpening();
    }
}

void AEatCoinGameState::AwardTopPlayers()
{
    // 코인 점수에 따라 내림차순으로 정렬
    PlayerCoinScores.Sort([](const AEatCoinPlayerState& A, const AEatCoinPlayerState& B) {
        return A.GetCoinScore() > B.GetCoinScore();
        });

    // 상위 3명의 플레이어에게 점수 부여
    const int32 NumTopPlayers = FMath::Min(3, PlayerCoinScores.Num());
    for (int32 i = 0; i < NumTopPlayers; ++i)
    {
        AEatCoinPlayerState* TopPlayer = PlayerCoinScores[i];
        if (TopPlayer)
        {
            int32 ScoreToAward = 0;
            int32 GarnetToAward = 0;

            switch (i)
            {
            case 0: //1등
               ScoreToAward = 5;
               GarnetToAward = 3;
               break;
            case 1: //2등
                ScoreToAward = 3;
                GarnetToAward = 2;
                break;
            case 2: //3등
                ScoreToAward = 1;
                GarnetToAward = 1;
                break;  
            }

            APlayerController* PlayerController = TopPlayer->GetPlayerController();
            if (PlayerController)
            {
                AGeniusPlayerState* GeniusPlayerState = PlayerController->GetPlayerState<AGeniusPlayerState>();
                if (GeniusPlayerState)
                {
                    // GeniusPlayerState에 점수 저장. 
                    GeniusPlayerState->AddScore(ScoreToAward);
                    GeniusPlayerState->AddGarnetCount(GarnetToAward);
            
                    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
                    {
                        if (AMainGameHUD* HUD = (*It)->GetHUD<AMainGameHUD>())
                        {
                            if (UMainGameWidget* MainGameWidget = HUD->GetMainGameWidget())
                            {
                                MainGameWidget->UpdatePlayerList(PlayingPlayers);
                                MainGameWidget->UpdateGarnetCount();
                            }
                        }
                    }
                }
            }
        }
    }
}



void AEatCoinGameState::OnRep_MovePlayersToStart() const
{
    // PlayerStart 액터를 찾기 위한 변수
    APlayerStart* PlayerStart = nullptr;

    // 레벨에 있는 모든 PlayerStart 액터를 검색
    for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
    {
        PlayerStart = *It;
        break; // 첫 번째 PlayerStart를 찾으면 반복 종료
    }

    if (!PlayerStart)
    {
        UE_LOG(LogTemp, Error, TEXT("레벨에서 PlayerStart 액터를 찾을 수 없습니다."));
        return;
    }

    FVector PlayerStartLocation = PlayerStart->GetActorLocation();

    // 플레이어 컨트롤러를 순회하며 플레이어를 PlayerStart 위치로 이동
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PlayerController = Cast<APlayerController>(*It);
        if (PlayerController)
        {
            ATheGeniusPlanCharacter* TheGeniusPlanCharacter = Cast<ATheGeniusPlanCharacter>(PlayerController->GetPawn());
            if (TheGeniusPlanCharacter)
            {
               
                // 플레이어를 PlayerStart 위치로 이동
                TheGeniusPlanCharacter->SetActorLocation(PlayerStartLocation);
            }
        }
    }
}


void AEatCoinGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AEatCoinGameState, PlayerCoinScores);
    DOREPLIFETIME(AEatCoinGameState, ECGameCountdownTime);
}