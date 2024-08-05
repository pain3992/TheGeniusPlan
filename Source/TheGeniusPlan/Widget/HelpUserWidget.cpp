// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/HelpUserWidget.h"
#include "Components/Button.h"

void UHelpUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Back)
	{
		Button_Back->OnClicked.AddDynamic(this, &UHelpUserWidget::OnBackButtonClicked);
	}
}

void UHelpUserWidget::OnBackButtonClicked()
{
	RemoveFromParent();
}
