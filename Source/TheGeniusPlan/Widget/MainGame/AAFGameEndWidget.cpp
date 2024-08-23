// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameEndWidget.h"
#include "Components/TextBlock.h"

void UAAFGameEndWidget::SetTextBlock(FText& NewWinner)
{
	Winner->SetText(NewWinner);
}
