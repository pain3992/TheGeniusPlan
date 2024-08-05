// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainHallUserWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"

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
    if (HelpWidgetClass)
    {
        UUserWidget* HelpWidget = CreateWidget<UUserWidget>(GetWorld(), HelpWidgetClass);
        if (HelpWidget)
        {
            HelpWidget->AddToViewport();
        }
    }
}
