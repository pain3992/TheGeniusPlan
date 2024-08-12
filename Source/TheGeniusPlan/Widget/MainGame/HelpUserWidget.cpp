// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainGame/HelpUserWidget.h"
#include "Components/Button.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"

void UHelpUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Back)
	{
		Button_Back->OnClicked.AddDynamic(this, &UHelpUserWidget::OnBackButtonClicked);
	}
}

void UHelpUserWidget::SetHUD(AMainGameHUD* InHUD)
{
	HUD = InHUD;
}

void UHelpUserWidget::OnBackButtonClicked()
{
    if (HUD)
    {
        HUD->ShowWidget(MainGameWidgetType::MainGameWidget);
    }
}