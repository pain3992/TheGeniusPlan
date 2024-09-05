// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/MainGame/HelpUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "Kismet/GameplayStatics.h"


void UHelpUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Back)
	{
		Button_Back->OnClicked.AddDynamic(this, &UHelpUserWidget::OnBackButtonClicked);
	}
}

void UHelpUserWidget::SetHUD(AMainGameHUD* InHUD)
{
	HUD = InHUD;
}

void UHelpUserWidget::SetHintText(const FString& NewText)
{
    if (Text_Hint)
    {
        Text_Hint->SetText(FText::FromString(NewText));
    }
}

void UHelpUserWidget::SetAwardText(const FString& NewText)
{
    if (Text_Award)
    {
        Text_Award->SetText(FText::FromString(NewText));
    }
}

void UHelpUserWidget::UpdateTextBaseOnLevel()
{
    FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);

    if (CurrentLevelName == "MainLevel")
    {
        SetHintText(TEXT("The Genius Plan \n"
            "The Genius Plan에 오신 것을 환영합니다! \n"
            "다양한 게임에서 우승하여 점수를 획득해보세요. \n"
            "마지막 게임이 종료되었을 때, 가장 점수가 높은 사람이 우승합니다.")); // MainLevel 규칙 작성

        SetAwardText(TEXT("The Genius Plan \n"
            "게임마다 특별한 보상이 주어집니다.")); // MainLevel 보상 작성
    }
    else if (CurrentLevelName == "ECLevel")
    {
        SetHintText(TEXT("Eat Coin! \n"
            "제한시간 내에 많은 코인을 먹으세요.\n"
            "방 곳곳에는 게임 진행에 도움이 되는 다양한 아이템이 준비되어 있습니다.\n"
            "가장 많은 코인을 먹은 사람이 승리!")); // EC 규칙 작성

        SetAwardText(TEXT("Eat Coin! \n"
            "1등: 5점, 가넷 3개 \n"
            "2등: 3점, 가넷 2개 \n"
            "3등: 1점, 가넷 1개 \n"
            "점수는 마지막 라운드가 종료된 후, \n"
            "누적된 코인 점수에 따라 차등 지급됩니다.")); // EC 보상 작성
    }
    else if (CurrentLevelName == "AAFLevel")
    {
        SetHintText(TEXT("가장 마지막까지 살아남으세요. \n"
            "발로 밟은 블럭은 수초내에 사라집니다. \n"
            "떨어지면 탈락됩니다. \n")); // AAF 규칙 작성
        SetAwardText(TEXT("1등 : 4점, 가넷 2개 \n"
            "2등 : 2점, 가넷 1개 \n"
            "점수는 마지막 라운드가 종료된 후, \n"
            "누적된 총 점수에 따라 차등 지급됩니다.\n")); // AAF 보상 작성
    }
    else
    {
        SetHintText(TEXT("")); // 아무 조건에도 해당하지 않을 경우 빈 텍스트
    }
}

void UHelpUserWidget::OnBackButtonClicked()
{
    if (HUD)
    {
        HUD->ShowWidget(MainGameWidgetType::MainGameWidget);
    }
}

void UHelpUserWidget::SetVisibility(ESlateVisibility InVisibility)
{
    Super::SetVisibility(InVisibility);

    if (InVisibility == ESlateVisibility::Visible)
    {
        // 가시성이 변경될 때 텍스트를 업데이트
        UpdateTextBaseOnLevel();
    }
}
