// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "BluePrint/UserWidget.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AEatCoinHUD::AEatCoinHUD()
{
    static ConstructorHelpers::FClassFinder<UEatCoinWidget> CEatCoinWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/JiYoung/Widget/WG_EatCoinGame.WG_EatCoinGame_C'"));
    if (CEatCoinWidget.Succeeded())
    {
        EatCoinWidgetClass = CEatCoinWidget.Class;
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
}


