// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinEndWidget.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinMenualWidget.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinStartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AEatCoinHUD::AEatCoinHUD()
{
    static ConstructorHelpers::FClassFinder<UEatCoinWidget> CEatCoinWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/JiYoung/Widget/WG_EatCoinGame.WG_EatCoinGame_C'"));
    static ConstructorHelpers::FClassFinder<UEatCoinEndWidget> CEatCoinEndWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/JiYoung/Widget/WG_EatCoinGameEnd.WG_EatCoinGameEnd_C'"));
    static ConstructorHelpers::FClassFinder<UEatCoinMenualWidget> CEatCoinMenualWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/JiYoung/Widget/WG_EatCoinStartMenual.WG_EatCoinStartMenual_C'"));
    static ConstructorHelpers::FClassFinder<UEatCoinStartWidget> CEatCoinStartWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/JiYoung/Widget/WG_EatCoinGameStart.WG_EatCoinGameStart_C'"));

    if (CEatCoinWidget.Succeeded() && CEatCoinEndWidget.Succeeded() && CEatCoinMenualWidget.Succeeded() && CEatCoinStartWidget.Succeeded())
    {
        EatCoinWidgetClass = CEatCoinWidget.Class;
        EatCoinEndWidgetClass = CEatCoinEndWidget.Class;
        EatCoinMenualWidgetClass = CEatCoinMenualWidget.Class;
        EatCoinStartWidgetClass = CEatCoinStartWidget.Class;
    }
}

void AEatCoinHUD::BeginPlay()
{
    Super::BeginPlay();

    if (EatCoinWidgetClass)
    {
        EatCoinWidget = Cast<UEatCoinWidget>(CreateWidget(GetWorld(), EatCoinWidgetClass, TEXT("EatCoinHUD")));
        if (EatCoinWidget)
        {
            EatCoinWidget->AddToViewport();
        }
    }

    if (EatCoinEndWidgetClass)
    {
        EatCoinEndWidget = CreateWidget<UEatCoinEndWidget>(GetWorld(), EatCoinEndWidgetClass);
        if (EatCoinEndWidget)
        {
            EatCoinEndWidget->AddToViewport();
            EatCoinEndWidget->SetVisibility(ESlateVisibility::Collapsed);  // 처음에는 숨겨둠
        }
    }

    if (EatCoinMenualWidgetClass)
    {
        EatCoinMenualWidget = CreateWidget<UEatCoinMenualWidget>(GetWorld(), EatCoinMenualWidgetClass);
        if (EatCoinMenualWidget)
        {
            EatCoinMenualWidget->AddToViewport();
            EatCoinMenualWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    if (EatCoinStartWidgetClass)
    {
        EatCoinStartWidget = CreateWidget<UEatCoinStartWidget>(GetWorld(), EatCoinStartWidgetClass);
        if (EatCoinStartWidget)
        {
            EatCoinStartWidget->AddToViewport();
            EatCoinStartWidget->SetVisibility(ESlateVisibility::Collapsed);  // 처음에는 숨겨둠
        }
    }
}
void AEatCoinHUD::ShowECMenualWidget()
{
    if (EatCoinMenualWidget)
    {
        EatCoinMenualWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void AEatCoinHUD::ShowEatCoinEndWidget()
{
    if (EatCoinEndWidget)
    {
        EatCoinEndWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void AEatCoinHUD::CollapsedECEndWidget()
{
    if (EatCoinEndWidget)
    {
        EatCoinEndWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AEatCoinHUD::CollapsedECMenualWidget()
{
    if (EatCoinMenualWidget)
    {
        EatCoinMenualWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AEatCoinHUD::ShowGameStartWidget()
{
    if (EatCoinStartWidget)
    {
        EatCoinStartWidget->SetVisibility(ESlateVisibility::Visible);

        GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideWidget, this, &AEatCoinHUD::HideGameStartWidget, 1.0f, false);
    }
}

void AEatCoinHUD::HideGameStartWidget()
{
    if (EatCoinStartWidget)
    {
        EatCoinStartWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}




