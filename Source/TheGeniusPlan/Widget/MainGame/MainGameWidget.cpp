// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Widget/MainGame/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
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

    LoadData();
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

void UMainGameWidget::LoadData()
{
    UE_LOG(LogTemp, Warning, TEXT("LoadData is working."));
    // 현재 게임 상태를 가져옵니다
    if (AMainGameStateBase* GameState = GetWorld()->GetGameState<AMainGameStateBase>())
    {
        const TArray<UPlayerRankingData*>& PlayerRankings = GameState->PlayerRankings;

        // 데이터가 이미 준비된 경우
        if (PlayerRankings.Num() > 0)
        {
            UpdatePlayerList(PlayerRankings);
            UE_LOG(LogTemp, Warning, TEXT("UpdatePlayerList is ready."));
        }
        else
        {
            // 데이터가 준비되지 않았을 경우 대기 또는 로딩 처리
            UE_LOG(LogTemp, Warning, TEXT("No player rankings data available."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to get GameState."));
    }
}


void UMainGameWidget::UpdatePlayerList(const TArray<UPlayerRankingData*>& PlayerRankingDataArray)
{
    UE_LOG(LogTemp, Warning, TEXT("UpdatePlayerList is working."));
    if (ListView_PlayerRanking == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ListView_PlayerRanking is not assigned."));
        return;
    }

    if (PlayerRankingUserWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerRankingUserWidgetClass is not assigned."));
        return;
    }

    // 리스트뷰 초기화
    ListView_PlayerRanking->ClearListItems();

    // PlayerRankingDataArray를 순회하며 위젯을 생성하고 리스트뷰에 추가
    for (UPlayerRankingData* RankingData : PlayerRankingDataArray)
    {
        if (RankingData)
        {
            UPlayerRankingUserWidget* RankingWidget = CreateWidget<UPlayerRankingUserWidget>(GetWorld(), PlayerRankingUserWidgetClass);

            if (RankingWidget)
            {
                RankingWidget->SetPlayerName(RankingData->PlayerName);
                RankingWidget->SetScore(RankingData->Score);

                ListView_PlayerRanking->AddItem(RankingWidget);
                UE_LOG(LogTemp, Warning, TEXT("Add Ranking Widget Sucessful."));
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to create RankingWidget."));
            }
        }
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

