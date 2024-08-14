// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowPlayerSeletedLandWidget.h"
#include "Components/TextBlock.h"

void UShowPlayerSeletedLandWidget::SetTextBox(const uint8& AbundanceNumber, const uint8& FamineNumber)
{
	FText Abundance = FText::AsNumber(AbundanceNumber);
	FText Famine = FText::AsNumber(FamineNumber);

	ALand->SetText(Abundance);
	FLand->SetText(Famine);
}

void UShowPlayerSeletedLandWidget::SetTimer(float Time)
{
	FText TextTime = FText::AsNumber((int)Time);
	Timer->SetText(TextTime);
}
