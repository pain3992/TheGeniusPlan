// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/Entry/LoginWidget.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheGeniusPlan/HUD/EntryHUD.h"

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(ButtonLogin)
	{
		ButtonLogin->OnClicked.AddDynamic(this, &ULoginWidget::ClickedLogin);
	}
	if(ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &ULoginWidget::ClickedQuit);
	}
	if(ButtonSignUp)
	{
		ButtonSignUp->OnClicked.AddDynamic(this, &ULoginWidget::ClickedSignUp);
	}
}

void ULoginWidget::ClickedLogin()
{
	if (EntryHUD)
	{
		EntryHUD->ShowWidget(EntryWidgetType::EntryWidget);
		UE_LOG(LogTemp, Warning, TEXT("HUD is Vaild"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD is Null"));
	}
}

void ULoginWidget::ClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void ULoginWidget::ClickedSignUp()
{
	if (EntryHUD)
	{
		EntryHUD->ShowWidget(EntryWidgetType::SignupWidget);
	}
}
