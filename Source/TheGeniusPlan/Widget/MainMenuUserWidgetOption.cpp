// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainMenuUserWidgetOption.h"
#include "Components/Button.h"
#include "TheGeniusPlan/GameModes/MainMenuHUD.h"

void UMainMenuUserWidgetOption::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonGameStart)
	{
		ButtonGameStart->OnClicked.AddDynamic(this, &UMainMenuUserWidgetOption::ClickedGameStart);
	}
	if (ButtonOption)
	{
		ButtonOption->OnClicked.AddDynamic(this, &UMainMenuUserWidgetOption::ClickedOption);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &UMainMenuUserWidgetOption::ClickedQuit);
	}

}

void UMainMenuUserWidgetOption::ClickedGameStart()
{
	if(GameStartMenuHUD)
	{
		GameStartMenuHUD->ShowWidget(WidgetType::LobbyWidget);
	}
}

void UMainMenuUserWidgetOption::ClickedOption()
{
	if(GameStartMenuHUD)
	{
		GameStartMenuHUD->ShowWidget(WidgetType::OptionWidget);
	}

}

void UMainMenuUserWidgetOption::ClickedQuit()
{
	if (GameStartMenuHUD)
	{
		GameStartMenuHUD->ShowWidget(WidgetType::LoginWidget);
	}
}
