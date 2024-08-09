// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"


void UPlayerRankingUserWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    if (UPlayerRankingData* PlayerRankingData = Cast<UPlayerRankingData>(ListItemObject))
    {
        SetPlayerName(PlayerRankingData->PlayerName);
        SetScore(PlayerRankingData->Score);
    }
    else
    {
        // 기본 이름과 점수로 설정
        SetPlayerName(TEXT("Default Player"));
        SetScore(100);
    }
}

void UPlayerRankingUserWidget::SetPlayerName(const FString& NewPlayerName)
{
    PlayerName = NewPlayerName;
    if (Text_PlayerName)
    {
        Text_PlayerName->SetText(FText::FromString(PlayerName));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Text_PlayerName is nullptr"));
    }
}

void UPlayerRankingUserWidget::SetScore(int32 NewScore)
{
    Score = NewScore;
    if (Text_Score)
    {
        Text_Score->SetText(FText::AsNumber(Score));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Text_Score is nullptr"));
    }
}

