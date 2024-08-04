// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainMenuUserWidget.h"
#include "Components/Button.h"

void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(Button_Login)
	{
		Button_Login->OnClicked.AddDynamic(this, &UMainMenuUserWidget::TestFunction);
	}
}

void UMainMenuUserWidget::TestFunction()
{
	UE_LOG(LogTemp, Error, TEXT("User Clicked LoginButton!"));
}
