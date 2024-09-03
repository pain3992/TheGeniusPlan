// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/Entry/EntryWidget.h"
#include "Components/Button.h"
#include "TheGeniusPlan/HUD/EntryHUD.h"

void UEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ButtonGameStart)
	{
		ButtonGameStart->OnClicked.AddDynamic(this, &UEntryWidget::ClickedGameStart);
	}
	if (ButtonOption)
	{
		ButtonOption->OnClicked.AddDynamic(this, &UEntryWidget::ClickedOption);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &UEntryWidget::ClickedQuit);
	}
}

void UEntryWidget::ClickedGameStart()
{
	if(EntryHUD)
	{
		EntryHUD->ShowWidget(EntryWidgetType::LobbyWidget);
	}
}

void UEntryWidget::ClickedOption()
{
	if(EntryHUD)
	{
		EntryHUD->ShowWidget(EntryWidgetType::OptionWidget);
	}
}

void UEntryWidget::ClickedQuit()
{
	if (EntryHUD)
	{
		// 로그아웃시 로그인위젯 입력값 초기화
		EntryHUD->ResetWidget(EntryWidgetType::LoginWidget);
		// 로그인위젯으로 전환
		EntryHUD->ShowWidget(EntryWidgetType::LoginWidget);
	}
}
