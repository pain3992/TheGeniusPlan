// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/Widget/MainGame/CoinScoreItemWidget.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "Kismet/GameplayStatics.h"

void UEatCoinWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Set up a timer to update the boost timer every second
    GetWorld()->GetTimerManager().SetTimer(
        UpdateTimerHandle,
        this,
        &UEatCoinWidget::UpdateBoostTimer,
        1.0f, // Update interval
        true // Looping
    );
}

void UEatCoinWidget::UpdateEatCoinPlayerList(const TArray<AGeniusPlayerState*>& PlayingPlayersArray)
{
    UE_LOG(LogTemp, Warning, TEXT("UpdateEatCoinPlayerList함수 실행")); //
    if (ListView_CoinScore == nullptr || CoinScoreItemWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ListView_CoinScore or CoinScoreItemWidgetClass is not assigned."));
        return;
    }

    // Create and add items
    TArray<UPlayerRankingData*> PlayerRankingDataArray;

    for (AGeniusPlayerState* PlayerState : PlayingPlayersArray)
    {
        if (PlayerState)
        {
            UPlayerRankingData* PlayerRankingData = NewObject<UPlayerRankingData>(this);
            PlayerRankingData->PlayerName = PlayerState->GetPlayerName();
            PlayerRankingData->Score = PlayerState->GetPlayerScore();

            PlayerRankingDataArray.Add(PlayerRankingData);
        }
    }

    // Sort the array based on scores
    PlayerRankingDataArray.Sort([](const UPlayerRankingData& A, const UPlayerRankingData& B)
        { return A.Score > B.Score; });

    // Clear and re-add sorted items to the ListView
    ListView_CoinScore->ClearListItems();
    for (UPlayerRankingData* RankingData : PlayerRankingDataArray)
    {
        ListView_CoinScore->AddItem(RankingData);
    }

    // Refresh the ListView
    ListView_CoinScore->RequestRefresh();
}

void UEatCoinWidget::UpdateBoostTimer()
{
    if (Text_BoostTimer)
    {
        AEatCoinGameMode* GameMode = Cast<AEatCoinGameMode>(UGameplayStatics::GetGameMode(this));
        if (GameMode)
        {
            // 남은 시간을 정수로 변환
            int32 RemainingTime = FMath::CeilToInt(GameMode->GetRemainingBoostTime());
            FText BoostTimeText = FText::FromString(FString::Printf(TEXT("%d"), RemainingTime));
            Text_BoostTimer->SetText(BoostTimeText);
        }
    }
}


