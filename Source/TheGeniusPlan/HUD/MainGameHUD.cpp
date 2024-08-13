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
    static ConstructorHelpers::FClassFinder<UMainGameWidget> CMainGameWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MainHallContent/Widget/WG_MainGameWidget.WG_MainGameWidget_C'"));
    static ConstructorHelpers::FClassFinder<UHelpUserWidget> CHelpWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MainHallContent/Widget/WG_Help.WG_Help_C'"));
    if (CMainGameWidget.Succeeded() && CHelpWidget.Succeeded())
    {
        MainGameWidgetClass = CMainGameWidget.Class;
        HelpWidgetClass = CHelpWidget.Class;
    }
}

void AMainGameHUD::BeginPlay()
{
    Super::BeginPlay();

    check(MainGameWidgetClass);
    check(HelpWidgetClass);

    MainGameWidget = Cast<UMainGameWidget>(CreateWidget(GetWorld(), MainGameWidgetClass, TEXT("MainGameHUD")));
    if (MainGameWidget)
    {
        MainGameWidget->AddToViewport();
        MainGameWidget->SetHUD(this);
    }

    HelpWidget = Cast<UHelpUserWidget>(CreateWidget(GetWorld(), HelpWidgetClass, TEXT("HelpHUD")));
    if (HelpWidget)
    {
        HelpWidget->AddToViewport();
        HelpWidget->SetVisibility(ESlateVisibility::Collapsed);
        HelpWidget->SetHUD(this);
    }

    //// Call UpdatePlayerRankings with a slight delay to ensure widgets are initialized
    //GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
    //    {
    //        // Ensure that MainGameWidget is properly initialized
    //        if (MainGameWidget)
    //        {
    //            AMainGameStateBase* GameState = GetWorld()->GetGameState<AMainGameStateBase>();
    //            if (GameState)
    //            {
    //                GameState->UpdatePlayerRankings();
    //            }
    //        }
    //    });
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
//        AGameState* GameState = GetWorld()->GetGameState<AMainHallGameState>();
//        if (GameState)
//        {
//            MainHallWidget->UpdateRankingList(GameState->PlayerRankings);
//        }
//    }
//}
