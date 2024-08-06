// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/SignupWidget.h"
#include "Components/Button.h"
#include "TheGeniusPlan/GameModes/MainMenuHUD.h"

void USignupWidget::NativeConstruct()
{
	if(ButtonCansel)
	{
		ButtonCansel->OnClicked.AddDynamic(this, &USignupWidget::ClickedButtonCansel);
	}

	if(ButtonSignup)
	{
		ButtonSignup->OnClicked.AddDynamic(this, &USignupWidget::ClickedButtonSignup);
	}
}

void USignupWidget::ClickedButtonSignup()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void USignupWidget::ClickedButtonCansel()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
