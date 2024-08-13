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
    if (Button_Help)
    {
        Button_Help->OnClicked.AddDynamic(this, &UMainGameWidget::OnHelpButtonClicked);
    }

   /* if (AMainGameStateBase* GameState = GetWorld()->GetGameState<AMainGameStateBase>())
    {
        const TArray<AGeniusPlayerState*>& PlayingPlayers = GameState->PlayingPlayers;
        UpdatePlayerList(PlayingPlayers);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get GameState."));
    }*/
}



//void UMainGameWidget::LoadData()
//{
//    UE_LOG(LogTemp, Warning, TEXT("LoadData is working."));
//    // 현재 게임 상태를 가져옵니다
//    if (AMainGameStateBase* GameState = GetWorld()->GetGameState<AMainGameStateBase>())
//    {
//        const TArray<UPlayerRankingData*>& PlayerRankings = GameState->PlayerRankings;
//
//        // 데이터가 이미 준비된 경우
//        if (PlayerRankings.Num() > 0)
//        {
//            UpdatePlayerList(PlayerRankings);
//            UE_LOG(LogTemp, Warning, TEXT("UpdatePlayerList is ready."));
//        }
//        else
//        {
//            // 데이터가 준비되지 않았을 경우 대기 또는 로딩 처리
//            UE_LOG(LogTemp, Warning, TEXT("No player rankings data available."));
//        }
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Failed to get GameState."));
//    }
//}

// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Log"));


void UMainGameWidget::UpdatePlayerList(const TArray<AGeniusPlayerState*>& PlayingPlayersArray)
{
    if (ListView_PlayerRanking == nullptr || PlayerRankingUserWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ListView_PlayerRanking or PlayerRankingUserWidgetClass is not assigned."));
        return;
    }

    // 리스트뷰 초기화
    ListView_PlayerRanking->ClearListItems();

    // PlayingPlayers 배열을 반복하여 각 플레이어에 대한 위젯 생성
    for (AGeniusPlayerState* PlayerState : PlayingPlayersArray)
    {
        if (PlayerState)
        {
            // 새로운 PlayerRankingUserWidget 인스턴스를 생성
            if (UPlayerRankingUserWidget* RankingWidget = CreateWidget<UPlayerRankingUserWidget>(GetWorld(), PlayerRankingUserWidgetClass))
            {
                // PlayerState의 정보를 이용해 위젯의 정보를 설정
                RankingWidget->SetPlayerName(PlayerState->GetPlayerName());
                RankingWidget->SetScore(PlayerState->GetPlayerScore());

                // 리스트뷰에 위젯 추가
                ListView_PlayerRanking->AddItem(RankingWidget);
                UE_LOG(LogTemp, Log, TEXT("Added RankingWidget to ListView for player: %s"), *PlayerState->GetPlayerName());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to create RankingWidget."));
            }
        }
    }
}

//void UMainGameWidget::UpdatePlayerList(const TArray<AGeniusPlayerState*>& PlayingPlayersArray);
//{
//    if (ListView_PlayerRanking == nullptr || PlayerRankingUserWidgetClass == nullptr)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("ListView_PlayerRanking or PlayerRankingUserWidgetClass is not assigned."));
//        return;
//    }
//
//    // 리스트뷰 초기화
//    ListView_PlayerRanking->ClearListItems();
//
//    // PlayerRankingDataArray를 순회하며 위젯을 생성하고 리스트뷰에 추가
//    for (UPlayerRankingData* RankingData : PlayerRankingDataArray)
//    {
//        if (RankingData)
//        {
//            // Create a new PlayerRankingUserWidget instance
//            UPlayerRankingUserWidget* RankingWidget = CreateWidget<UPlayerRankingUserWidget>(GetWorld(), PlayerRankingUserWidgetClass);
//
//            if (RankingWidget)
//            {
//                // Set the data for the widget
//                RankingWidget->SetPlayerName(RankingData->PlayerName);
//                RankingWidget->SetScore(RankingData->Score);
//
//                // Add the widget to the ListView
//                ListView_PlayerRanking->AddItem(RankingWidget);
//                UE_LOG(LogTemp, Log, TEXT("Added RankingWidget to ListView."));
//            }
//            else
//            {
//                UE_LOG(LogTemp, Warning, TEXT("Failed to create RankingWidget."));
//            }
//        }
//    }
//}

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


