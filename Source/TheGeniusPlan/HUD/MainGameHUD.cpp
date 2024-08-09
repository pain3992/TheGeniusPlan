// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/HUD/MainGameHUD.h"

#include "TheGeniusPlan/Widget/MainGame/ChangeGameModeWidget.h"

AMainGameHUD::AMainGameHUD()
{
	static ConstructorHelpers::FClassFinder<UChangeGameModeWidget> CChangeGameModeWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/JangHun/MainGame/Widget/WBP_ChangeGameMode.WBP_ChangeGameMode_C'"));
																							   

	if (CChangeGameModeWidget.Succeeded())
	{
		ChangeGameModeWidgetClass = CChangeGameModeWidget.Class;
	}
}

void AMainGameHUD::BeginPlay()
{
	Super::BeginPlay();

	check(ChangeGameModeWidgetClass);

	ChangeGameModeWidget = Cast<UChangeGameModeWidget>(CreateWidget(GetWorld(), ChangeGameModeWidgetClass, TEXT("MainGameHUD")));
	// 위젯 Viewport 등록
	if (ChangeGameModeWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ChangeGameModeWidget"));
		ChangeGameModeWidget->MainGameHUD = this;
		ChangeGameModeWidget->AddToViewport();
	}
}