// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainGame/EatCoinMenualWidget.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"

void UEatCoinMenualWidget::NativeConstruct()
{
}


void UEatCoinMenualWidget::UpdateStartEatCoinCountdownDisplay(int32 CountdownTimeInSeconds)
{
    int32 Minutes = CountdownTimeInSeconds / 60;
    int32 Seconds = CountdownTimeInSeconds % 60;
    FString CountdownText;
    if (Minutes > 0)
    {
        CountdownText = FString::Printf(TEXT("%d:%02d"), Minutes, Seconds);
    }
    else
    {
        CountdownText = FString::Printf(TEXT("%d"), Seconds);
    }

    if (Text_StartTimer)
    {
        Text_StartTimer->SetText(FText::FromString(CountdownText));
    }
}