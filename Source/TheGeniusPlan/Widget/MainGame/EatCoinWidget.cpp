// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "Components/ListView.h"
#include "Blueprint/UserWidget.h"
#include "TheGeniusPlan/Data/PlayerRankingData.h"
#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "TheGeniusPlan/Widget/MainGame/CoinScoreItemWidget.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/Player/EatCoinPlayerState.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"



void UEatCoinWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Set up a timer to update the boost timer every second
    GetWorld()->GetTimerManager().SetTimer(
        UpdateTimerHandle,
        this,
        &UEatCoinWidget::UpdateBoostTimer,
        0.1f, // Update interval
        true // Looping
    );
}

void UEatCoinWidget::UpdateEatCoinPlayerList(const TArray<AEatCoinPlayerState*>& PlayerCoinScoresArray)
{
    UE_LOG(LogTemp, Warning, TEXT("UpdateEatCoinPlayerList function executed"));

    if (ListView_CoinScore == nullptr || CoinScoreItemWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ListView_CoinScore or CoinScoreItemWidgetClass is not assigned."));
        return;
    }

    TArray<UPlayerRankingData*> PlayerRankingDataArray;

    for (AEatCoinPlayerState* EatCoinPlayerState : PlayerCoinScoresArray)
    {
        if (EatCoinPlayerState)
        {
            UPlayerRankingData* PlayerRankingData = NewObject<UPlayerRankingData>(this);
            PlayerRankingData->PlayerName = EatCoinPlayerState->GetPlayerName();
            PlayerRankingData->CoinScore = EatCoinPlayerState->GetCoinScore();
            PlayerRankingDataArray.Add(PlayerRankingData);
        }
    }

    PlayerRankingDataArray.Sort([](const UPlayerRankingData& A, const UPlayerRankingData& B)
        {
            return A.CoinScore > B.CoinScore;
        });

    ListView_CoinScore->ClearListItems();
    for (UPlayerRankingData* RankingData : PlayerRankingDataArray)
    {
        ListView_CoinScore->AddItem(RankingData);
    }

    ListView_CoinScore->RequestRefresh();
}

void UEatCoinWidget::UpdateBoostTimer()
{
    if (Text_BoostTimer)
    {
        APlayerController* PlayerController = GetOwningPlayer();
        if (PlayerController)
        {
            AEatCoinPlayerState* PlayerState = PlayerController->GetPlayerState<AEatCoinPlayerState>();
            if (PlayerState)
            {
                // Display the remaining boost time
                int32 RemainingTime = FMath::CeilToInt(PlayerState->BoostTimeLeft);
                FText BoostTimeText = FText::FromString(FString::Printf(TEXT("%d"), RemainingTime));
                Text_BoostTimer->SetText(BoostTimeText);
            }
        }
    }
}

void UEatCoinWidget::MoveListViewToCenter()
{
    if (ListView_CoinScore && ListView_CoinScore->GetParent())
    {
        UVerticalBox* VerticalBoxParent = Cast<UVerticalBox>(ListView_CoinScore->GetParent());

        if (VerticalBoxParent && VerticalBoxParent->GetParent())
        {
            UBorder* BorderParent = Cast<UBorder>(VerticalBoxParent->GetParent());

            if (BorderParent)
            {
                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(BorderParent->Slot);
                if (CanvasSlot)
                {
                    // 현재 위치 값을 가져옵니다.
                    FVector2D CurrentPosition = CanvasSlot->GetPosition();

                    // X 값을 0으로 설정하고 Y 값은 기존 값으로 유지합니다.
                    CanvasSlot->SetPosition(FVector2D(0.0f, CurrentPosition.Y));

                    UE_LOG(LogTemp, Warning, TEXT("Border의 X 포지션을 0으로 이동했습니다."));
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Border의 Slot을 CanvasPanelSlot으로 캐스팅하는 데 실패했습니다."));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("VerticalBox의 부모가 UBorder가 아닙니다."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ListView의 부모가 UVerticalBox가 아닙니다."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ListView_CoinScore가 유효하지 않거나 부모가 없습니다."));
    }
}

void UEatCoinWidget::MoveListViewToOriginalPosition()
{
    if (ListView_CoinScore && ListView_CoinScore->GetParent())
    {
        UVerticalBox* VerticalBoxParent = Cast<UVerticalBox>(ListView_CoinScore->GetParent());

        if (VerticalBoxParent && VerticalBoxParent->GetParent())
        {
            UBorder* BorderParent = Cast<UBorder>(VerticalBoxParent->GetParent());

            if (BorderParent)
            {
                UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(BorderParent->Slot);
                if (CanvasSlot)
                {
                    // X 값을 600으로 설정하고 Y 값은 현재 값을 유지합니다.
                    FVector2D CurrentPosition = CanvasSlot->GetPosition();
                    CanvasSlot->SetPosition(FVector2D(600.0f, CurrentPosition.Y));

                    UE_LOG(LogTemp, Warning, TEXT("Border의 X 포지션을 600으로 이동했습니다."));
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Border의 Slot을 CanvasPanelSlot으로 캐스팅하는 데 실패했습니다."));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("VerticalBox의 부모가 UBorder가 아닙니다."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ListView의 부모가 UVerticalBox가 아닙니다."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ListView_CoinScore가 유효하지 않거나 부모가 없습니다."));
    }
}

