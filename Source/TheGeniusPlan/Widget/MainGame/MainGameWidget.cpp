// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Widget/MainGame/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"

void UMainGameWidget::NativeConstruct()
{
    Super::NativeConstruct();
    UE_LOG(LogTemp, Log, TEXT("UMainHallUserWidget::NativeConstruct called"));

    // 버튼 클릭 이벤트 처리
    if (Button_Hint)
    {
        Button_Hint->OnClicked.AddDynamic(this, &UMainGameWidget::OnHelpButtonClicked);
    }
}

void UMainGameWidget::UpdatePlayerList(const TArray<AGeniusPlayerState*>& PlayingPlayersArray)
{
    if (ListView_PlayerRanking == nullptr || PlayerRankingUserWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ListView_PlayerRanking or PlayerRankingUserWidgetClass is not assigned."));
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
        {
            return A.Score > B.Score;
        });

    // Clear and re-add sorted items to the ListView
    ListView_PlayerRanking->ClearListItems();
    for (UPlayerRankingData* RankingData : PlayerRankingDataArray)
    {
        ListView_PlayerRanking->AddItem(RankingData);
    }

    // Refresh the ListView
    ListView_PlayerRanking->RequestRefresh();
}


void UMainGameWidget::UpdateCountdownDisplay(int32 CountdownTimeInSeconds)
{
    int32 Minutes = CountdownTimeInSeconds / 60;
    int32 Seconds = CountdownTimeInSeconds % 60;
    FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

    if (Text_Countdown)
    {
        Text_Countdown->SetText(FText::FromString(CountdownText));
    }
}

void UMainGameWidget::OnHelpButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Is Work!"));
	if (MainGameHUD)
	{
		MainGameHUD->ShowWidget(MainGameWidgetType::HelpWidget);
	}
}

void UMainGameWidget::SetHUD(AMainGameHUD *InHUD)
{
	MainGameHUD = InHUD;
    UE_LOG(LogTemp, Log, TEXT("HUD successfully set in MainGameWidget."));
}


