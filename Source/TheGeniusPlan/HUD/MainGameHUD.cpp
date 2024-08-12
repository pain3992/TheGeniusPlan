// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "BluePrint/UserWidget.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "TheGeniusPlan/Widget/MainGame/HelpUserWidget.h"
#include "TheGeniusPlan/Widget/MainGame/PlayerRankingUserWidget.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "Kismet/GameplayStatics.h"

AMainGameHUD::AMainGameHUD()
{
    Super::BeginPlay();

    // static ConstructorHelpers::FClassFinder<UMainGameWidget> CMainGameWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MainHallContent/Widget/WG_MainHallWidget.WG_MainHallWidget_C'"));
    // static ConstructorHelpers::FClassFinder<UHelpUserWidget> CHelpWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MainHallContent/Widget/WG_Help.WG_Help_C'"));
    // if (CMainGameWidget.Succeeded() && CHelpWidget.Succeeded())
    // {
    //     MainGameWidgetClass = CMainGameWidget.Class;
    //     HelpWidgetClass = CHelpWidget.Class;
    // }
    // check(MainGameWidgetClass);
    //
    // MainGameWidget = Cast<UMainGameWidget>(CreateWidget<UMainGameWidget>(GetWorld(), MainGameWidgetClass, TEXT("MainGameHUD")));
    // if (MainGameWidget)
    // {
    //     MainGameWidget->SetHUD(this);  // Set HUD reference for MainGameWidget
    //     MainGameWidget->MainGameHUD = this;
    //     MainGameWidget->AddToViewport();
    //     UE_LOG(LogTemp, Log, TEXT("MainGameWidget successfully created and added to viewport."));
    // }
    //
    // HelpWidget = CreateWidget<UHelpUserWidget>(GetWorld(), HelpWidgetClass, TEXT("HelpHUD"));
    // if (HelpWidget)
    // {
    //     HelpWidget->AddToViewport();
    //     HelpWidget->SetVisibility(ESlateVisibility::Collapsed);  // Hide HelpWidget initially
    //     HelpWidget->SetHUD(this);  // Set HUD reference for HelpWidget
    //     UE_LOG(LogTemp, Log, TEXT("HelpWidget successfully created and added to viewport."));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Error, TEXT("Failed to create HelpWidget. Make sure the widget class is properly assigned in the HUD."));
    // }
}

void AMainGameHUD::BeginPlay()
{
   
}

void AMainGameHUD::ShowWidget(MainGameWidgetType type)
{
    switch (type)
    {
    case MainGameWidgetType::NONE:
        MainGameWidget->SetVisibility(ESlateVisibility::Visible);
        HelpWidget->SetVisibility(ESlateVisibility::Collapsed);
        ShowMouseCursor(false);
        break;
    case MainGameWidgetType::MainGameWidget:
        MainGameWidget->SetVisibility(ESlateVisibility::Visible);
        HelpWidget->SetVisibility(ESlateVisibility::Collapsed);
        ShowMouseCursor(false);
        break;
    case MainGameWidgetType::HelpWidget:
        MainGameWidget->SetVisibility(ESlateVisibility::Collapsed);
        HelpWidget->SetVisibility(ESlateVisibility::Visible);
        ShowMouseCursor(true); // 커서를 보이도록 설정
        break;
    case MainGameWidgetType::MAX:
        break;
    default:
        break;
    }
}

void AMainGameHUD::SetHelpWidgetVisibility(ESlateVisibility Visibility)
{
    if (HelpWidget)
    {
        HelpWidget->SetVisibility(Visibility);
    }
}

void AMainGameHUD::ShowMouseCursor(bool bShowCursor)
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
