// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidget.h"
#include "Components/TextBlock.h"

void UTimerWidget::UpdateTime(double NewTime)
{
	Time->SetText(FText::AsNumber(NewTime));
}
