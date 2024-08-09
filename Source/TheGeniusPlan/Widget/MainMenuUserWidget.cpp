// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainMenuUserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "TheGeniusPlan/GameModes/MainMenuHUD.h"

void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(ButtonLogin)
	{
		ButtonLogin->OnClicked.AddDynamic(this, &UMainMenuUserWidget::ClickedLogin);
	}
	if(ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &UMainMenuUserWidget::ClickedQuit);
	}
	if(ButtonSignUp)
	{
		ButtonSignUp->OnClicked.AddDynamic(this, &UMainMenuUserWidget::ClickedSignUp);

	}
}

void UMainMenuUserWidget::ClickedLogin()
{
	if (LoginMenuHUD)
	{
		LoginMenuHUD->ShowWidget(WidgetType::StartWidget);
		UE_LOG(LogTemp, Warning, TEXT("HUD is Vaild"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD is Null"));

	}

}

void UMainMenuUserWidget::ClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UMainMenuUserWidget::ClickedSignUp()
{
	if(LoginMenuHUD)
	{
		LoginMenuHUD->ShowWidget(WidgetType::SignupWidget);
	}

}
