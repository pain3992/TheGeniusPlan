// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/HUD/MainHallHUD.h"
#include "BluePrint/UserWidget.h"

void AMainHallHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget <UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
