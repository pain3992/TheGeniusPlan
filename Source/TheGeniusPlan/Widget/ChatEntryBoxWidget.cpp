// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/ChatEntryBoxWidget.h"
#include "Components/TextBlock.h"

void UChatEntryBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(TextBox)
	{
		TextBox->SetText(FText::FromString(Message));
	}

}
