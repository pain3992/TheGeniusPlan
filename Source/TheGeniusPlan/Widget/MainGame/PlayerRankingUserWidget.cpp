// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/Widget/MainGame/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

void UPlayerRankingUserWidget::NativeOnListItemObjectSet(UObject *ListItemObject)
{
    // Ensure that the ListItemObject is of type UPlayerRankingData
    if (UPlayerRankingData *RankingData = Cast<UPlayerRankingData>(ListItemObject))
    {
        // Use the data from RankingData to set the PlayerName and Score
        SetPlayerName(RankingData->PlayerName);
        SetScore(RankingData->Score);
    }
    else
    {
        // If ListItemObject is not valid or not of the expected type, set default values
        SetPlayerName(TEXT("Default Player"));
        SetScore(100);
        UE_LOG(LogTemp, Warning, TEXT("ListItemObject is not of type UPlayerRankingData."));
    }

    if (ListItemObject)
    {
        UE_LOG(LogTemp, Log, TEXT("ListItemObject Type: %s"), *ListItemObject->GetClass()->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ListItemObject is nullptr."));
    }
}

void UPlayerRankingUserWidget::SetPlayerName(const FString &NewPlayerName)
{
    PlayerName = NewPlayerName;
    if (Text_PlayerName)
    {
        Text_PlayerName->SetText(FText::FromString(PlayerName));
        UE_LOG(LogTemp, Log, TEXT("SetPlayerName called with: %s"), *PlayerName); // Debug log
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
        UE_LOG(LogTemp, Log, TEXT("SetScore called with: %d"), Score); // Debug log
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Text_Score is nullptr"));
    }
}
