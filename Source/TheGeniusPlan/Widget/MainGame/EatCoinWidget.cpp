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
#include "TheGeniusPlan/Player/EatCoinPlayerState.h"

void UEatCoinWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Set up a timer to update the boost timer every second
    GetWorld()->GetTimerManager().SetTimer(
        UpdateTimerHandle,
        this,
        &UEatCoinWidget::UpdateBoostTimer,
        0.1f, // Update interval
        true // Looping
    );
}

void UEatCoinWidget::UpdateEatCoinPlayerList(const TArray<AEatCoinPlayerState*>& PlayerCoinScoresArray)
{
    UE_LOG(LogTemp, Warning, TEXT("UpdateEatCoinPlayerList함수 실행")); //
    if (ListView_CoinScore == nullptr || CoinScoreItemWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ListView_CoinScore or CoinScoreItemWidgetClass is not assigned."));
        return;
    }

    // Create and add items
    TArray<UPlayerRankingData*> PlayerRankingDataArray;

    for (AEatCoinPlayerState* EatCoinPlayerState : PlayerCoinScoresArray) 
    {
        if (EatCoinPlayerState)
        {
            UPlayerRankingData* PlayerRankingData = NewObject<UPlayerRankingData>(this);
            PlayerRankingData->PlayerName = EatCoinPlayerState->GetPlayerName();
            PlayerRankingData->CoinScore = EatCoinPlayerState->GetCoinScore();
           

            PlayerRankingDataArray.Add(PlayerRankingData);
        }
    }


    // Sort the array based on scores
    PlayerRankingDataArray.Sort([](const UPlayerRankingData& A, const UPlayerRankingData& B)
        { return A.Score > B.Score; });


    ListView_CoinScore;

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
        APlayerController* PlayerController = GetOwningPlayer();
        if (PlayerController)
        {
            AEatCoinPlayerState* PlayerState = PlayerController->GetPlayerState<AEatCoinPlayerState>();
            if (PlayerState)
            {
                // Display the remaining boost time
                int32 RemainingTime = FMath::CeilToInt(PlayerState->BoostTimeLeft);
                FText BoostTimeText = FText::FromString(FString::Printf(TEXT("%d"), RemainingTime));
                Text_BoostTimer->SetText(BoostTimeText);
            }
        }
    }
}


