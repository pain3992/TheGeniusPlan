// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/HUD/ChangeGameModeHUD.h"
#include "TheGeniusPlan/Widget/MainGame/ChangeGameModeWidget.h"

AChangeGameModeHUD::AChangeGameModeHUD()
{
	static ConstructorHelpers::FClassFinder<UChangeGameModeWidget> CChangeGameModeWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/JangHun/MainGame/Widget/WBP_ChangeGameMode.WBP_ChangeGameMode_C'"));
																							   

	if (CChangeGameModeWidget.Succeeded())
	{
		ChangeGameModeWidgetClass = CChangeGameModeWidget.Class;
	}
}

void AChangeGameModeHUD::BeginPlay()
{
	Super::BeginPlay();

	check(ChangeGameModeWidgetClass);

	ChangeGameModeWidget = Cast<UChangeGameModeWidget>(CreateWidget(GetWorld(), ChangeGameModeWidgetClass, TEXT("MainGameHUD")));
	// 위젯 Viewport 등록
	if (ChangeGameModeWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ChangeGameModeWidget"));
		ChangeGameModeWidget->ChangeGameModeHUD = this;
		ChangeGameModeWidget->AddToViewport();
	}
}