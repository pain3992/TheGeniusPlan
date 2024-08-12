// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/HUD/MainHallHUD.h"
#include "BluePrint/UserWidget.h"
#include "TheGeniusPlan/Widget/MainHallUserWidget.h"
#include "TheGeniusPlan/Widget/HelpUserWidget.h"
#include "TheGeniusPlan/Widget/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/GameState/MainHallGameState.h"
#include "Kismet/GameplayStatics.h"

AMainHallHUD::AMainHallHUD()
{
	static ConstructorHelpers::FClassFinder<UMainHallUserWidget> CMainHallWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MainHallContent/Widget/WG_MainHallWidget.WG_MainHallWidget_C'"));
	static ConstructorHelpers::FClassFinder<UHelpUserWidget> CHelpWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MainHallContent/Widget/WG_Help.WG_Help_C'"));
	if (CMainHallWidget.Succeeded() && CHelpWidget.Succeeded())
	{
		MainHallWidgetClass = CMainHallWidget.Class;
		HelpWidgetClass = CHelpWidget.Class;
	}
    
    MainHallWidget = Cast<UMainHallUserWidget>(CreateWidget<UMainHallUserWidget>(GetWorld(), MainHallWidgetClass, TEXT("MainHallHUD")));    check(MainHallWidgetClass);
    check(HelpWidgetClass);
    MainHallWidget = Cast<UMainHallUserWidget>(CreateWidget<UMainHallUserWidget>(GetWorld(), MainHallWidgetClass, TEXT("MainHallHUD")));
    if (MainHallWidget)
    {
        MainHallWidget->SetHUD(this);  // Set HUD reference for MainHallWidget
        MainHallWidget->MainHallHUD = this;
        MainHallWidget->AddToViewport();
        UE_LOG(LogTemp, Log, TEXT("MainHallWidget successfully created and added to viewport."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create MainHallWidget. Make sure the widget class is properly assigned in the HUD."));
    }
}

void AMainHallHUD::BeginPlay()
{
    Super::BeginPlay();

    HelpWidget = CreateWidget<UHelpUserWidget>(GetWorld(), HelpWidgetClass, TEXT("HelpHUD"));
    if (HelpWidget)
    {
        HelpWidget->AddToViewport();
        HelpWidget->SetVisibility(ESlateVisibility::Collapsed);  // Hide HelpWidget initially
        HelpWidget->SetHUD(this);  // Set HUD reference for HelpWidget
        UE_LOG(LogTemp, Log, TEXT("HelpWidget successfully created and added to viewport."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create HelpWidget. Make sure the widget class is properly assigned in the HUD."));
    }
}

void AMainHallHUD::ShowWidget(MainHallWidgetType type)
{
    switch (type)
    {
    case MainHallWidgetType::NONE:
        MainHallWidget->SetVisibility(ESlateVisibility::Visible);
        HelpWidget->SetVisibility(ESlateVisibility::Collapsed);
        ShowMouseCursor(false);
        break;
    case MainHallWidgetType::MainHallWidget:
        MainHallWidget->SetVisibility(ESlateVisibility::Visible);
        HelpWidget->SetVisibility(ESlateVisibility::Collapsed);
        ShowMouseCursor(false);
        break;
    case MainHallWidgetType::HelpWidget:
        MainHallWidget->SetVisibility(ESlateVisibility::Collapsed);
        HelpWidget->SetVisibility(ESlateVisibility::Visible);
        ShowMouseCursor(true); // 커서를 보이도록 설정
        break;
    case MainHallWidgetType::MAX:
        break;
    default:
        break;
    }
}

void AMainHallHUD::SetHelpWidgetVisibility(ESlateVisibility Visibility)
{
    if (HelpWidget)
    {
        HelpWidget->SetVisibility(Visibility);
    }
}

void AMainHallHUD::ShowMouseCursor(bool bShowCursor)
{
    APlayerController *PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = bShowCursor;
        if (bShowCursor)
        {
            PlayerController->SetInputMode(FInputModeUIOnly());
        }
        else
        {
            PlayerController->SetInputMode(FInputModeGameOnly());
        }
    }
}

//void AMainHallHUD::UpdateRankingList()
//{
//    if (MainHallWidget)
//    {
//        // Retrieve the GameState and update the widget
//        AMainHallGameState* GameState = GetWorld()->GetGameState<AMainHallGameState>();
//        if (GameState)
//        {
//            MainHallWidget->UpdateRankingList(GameState->PlayerRankings);
//        }
//    }
//}
