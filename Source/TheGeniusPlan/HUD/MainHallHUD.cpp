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
}

void AMainHallHUD::BeginPlay()
{
    Super::BeginPlay();

    check(MainHallWidgetClass);
    check(HelpWidgetClass);

    MainHallWidget = Cast<UMainHallUserWidget>(CreateWidget(GetWorld(), MainHallWidgetClass, TEXT("MainHallHUD")));
    if (MainHallWidget)
    {
        MainHallWidget->AddToViewport();
        MainHallWidget->SetHUD(this);  // Set HUD reference for MainHallWidget
    }

    HelpWidget = Cast<UHelpUserWidget>(CreateWidget(GetWorld(), HelpWidgetClass, TEXT("HelpHUD")));
    if (HelpWidget)
    {
        HelpWidget->AddToViewport();
        HelpWidget->SetVisibility(ESlateVisibility::Collapsed);  // Hide HelpWidget initially
        HelpWidget->SetHUD(this);  // Set HUD reference for HelpWidget
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
        ShowMouseCursor(true); // Ŀ���� ���̵��� ����
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
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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

void AMainHallHUD::UpdateRankingList()
{
    if (MainHallWidget)
    {
        // Retrieve the GameState and update the widget
        AMainHallGameState* GameState = GetWorld()->GetGameState<AMainHallGameState>();
        if (GameState)
        {
            MainHallWidget->UpdateRankingList(GameState->PlayerRankings);
        }
    }
}
