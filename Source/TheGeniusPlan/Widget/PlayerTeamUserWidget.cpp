// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/PlayerTeamUserWidget.h"
#include "Components/TextBlock.h"


void UPlayerTeamUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Any additional setup if needed
}

void UPlayerTeamUserWidget::SetPlayerData(const FString& PlayerName, const FString& TeamName)
{
    if (Text_PlayerName)
    {
        Text_PlayerName->SetText(FText::FromString(PlayerName));
    }

    if (Text_TeamName)
    {
        Text_TeamName->SetText(FText::FromString(TeamName));
    }
}
