#include "TheGeniusPlan/gameModes/MainGame//MainGameStateBase.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "TheGeniusPlan/Widget/MainGame/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"

AMainGameStateBase::AMainGameStateBase()
{
    UE_LOG(LogTemp, Log, TEXT("AMainGameStateBase instance created."));
}

TArray<AGeniusPlayerState *> AMainGameStateBase::GetAllPlayerStates() const
{
    TArray<AGeniusPlayerState *> PlayerStates;

    // 모든 플레이어 상태를 가져옵니다.
    for (APlayerState *PlayerState : PlayerArray)
    {
        AGeniusPlayerState *GeniusPlayerState = Cast<AGeniusPlayerState>(PlayerState);
        if (GeniusPlayerState)
        {
            PlayerStates.Add(GeniusPlayerState);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("GetAllPlayerStates: %d player states found."), PlayerStates.Num());
    return PlayerStates;
}

void AMainGameStateBase::UpdatePlayerRankings()
{
    UE_LOG(LogTemp, Log, TEXT("UpdatePlayerRankings function started."));

    // 플레이어 상태를 모두 가져옵니다.
    TArray<AGeniusPlayerState *> PlayerStates = GetAllPlayerStates();

    // 점수에 따라 정렬
    PlayerStates.Sort([](const AGeniusPlayerState &A, const AGeniusPlayerState &B)
                      {
                          return A.GetPlayerScore() > B.GetPlayerScore(); // 높은 점수가 먼저 오도록 정렬
                      });

    // 생성된 UPlayerRankingData 객체를 저장할 배열을 초기화합니다.
    PlayerRankings.Empty(); // 기존 데이터 비우기

    // 정렬된 플레이어 상태를 기반으로 PlayerRankingData 객체를 생성하여 PlayerRankings에 추가합니다.
    for (AGeniusPlayerState *PlayerState : PlayerStates)
    {
        if (PlayerState)
        {
            UPlayerRankingData *RankingData = NewObject<UPlayerRankingData>();
            RankingData->PlayerName = PlayerState->PlayerName;
            RankingData->Score = PlayerState->GetPlayerScore();

            PlayerRankings.Add(RankingData);

            UE_LOG(LogTemp, Log, TEXT("UpdatePlayerRankings: Added player %s with score %d."), *RankingData->PlayerName, RankingData->Score);
        }
    }

    // 이후 MainHallUserWidget에서 이 데이터를 활용할 수 있도록 전달하거나 사용
    if (AMainGameHUD *HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AMainGameHUD>())
    {
        if (UMainGameWidget *MainGameWidget = HUD->GetMainGameWidget())
        {
            MainGameWidget->UpdatePlayerList(PlayerRankings);
            UE_LOG(LogTemp, Log, TEXT("UpdatePlayerRankings: Updated player rankings in MainHallUserWidget."));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("UpdatePlayerRankings: Failed to get MainHallUserWidget from HUD."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UpdatePlayerRankings: Failed to get HUD from player controller."));
    }
}
