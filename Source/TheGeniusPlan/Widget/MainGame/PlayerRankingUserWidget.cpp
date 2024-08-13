// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainGame/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"


void UPlayerRankingUserWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    UE_LOG(LogTemp, Log, TEXT("ListItemObject Class: %s"), *ListItemObject->GetClass()->GetName());
    
    UPlayerRankingUserWidget* PlayerRankingWidget = Cast<UPlayerRankingUserWidget>(ListItemObject);
    
    if (IsValid(ListItemObject) == false)
        return;

    UE_LOG(LogTemp, Log, TEXT("ListItemObject 11111"));
}

void UPlayerRankingUserWidget::SetPlayerName(const FString& NewPlayerName)
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

