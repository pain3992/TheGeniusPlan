// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLobbyWidget.h"
#include "Components/TextBlock.h"

void UGameLobbyWidget::ChangePlayerCount(int32 NewNumber)
{
	PlayerCount->SetText(FText::AsNumber(NewNumber));
}
