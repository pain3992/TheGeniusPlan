// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/PlayerRankingUserWidget.h"
#include "Components/TextBlock.h"

void UPlayerRankingUserWidget::UpdateData(const FPlayerRankingData& PlayerRankingData)
{
    if (Text_PlayerName)
    {
        Text_PlayerName->SetText(FText::FromString(PlayerRankingData.PlayerName));
    }
    if (Text_Score)
    {
        Text_Score->SetText(FText::AsNumber(PlayerRankingData.Score));
    }
}
