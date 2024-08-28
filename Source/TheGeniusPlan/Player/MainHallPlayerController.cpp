// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Player/MainHallPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "TheGeniusPlan/ChatComponent.h"

AMainHallPlayerController::AMainHallPlayerController()
{
	ChatComponent = CreateDefaultSubobject<UChatComponent>(TEXT("ChatComponent"));

	if (ChatComponent)
	{

	}
}
