// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainHallUserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Widget/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/GameModes/MainHallGameMode.h"
#include "TheGeniusPlan/HUD/MainHallHUD.h"
#include "Engine/Engine.h"


void UMainHallUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Help)
	{
		Button_Help->OnClicked.AddDynamic(this, &UMainHallUserWidget::OnHelpButtonClicked);
	}

}

void UMainHallUserWidget::OnHelpButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Is Work!"));
	if (HUD)
	{
		HUD->ShowWidget(MainHallWidgetType::HelpWidget);
	}
}

void UMainHallUserWidget::SetHUD(AMainHallHUD* InHUD)
{
	HUD = InHUD;
}

void UMainHallUserWidget::UpdateRankingList(const TArray<FPlayerRankingData>& Rankings)
{
    UE_LOG(LogTemp, Log, TEXT("Working..."));
    if (!ListView_PlayerRanking || !PlayerRankingUserWidgetClass)
    {
        return;
    }

    ListView_PlayerRanking->ClearListItems();

    for (const FPlayerRankingData& Ranking : Rankings)
    {
        UPlayerRankingUserWidget* NewItem = CreateWidget<UPlayerRankingUserWidget>(this, PlayerRankingUserWidgetClass);
        if (NewItem)
        {
            NewItem->UpdateData(Ranking);
            ListView_PlayerRanking->AddItem(NewItem);
        }
    }
}
