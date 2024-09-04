// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "TheGeniusPlan/Widget/MainGame/MainGameWidget.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "Net/UnrealNetwork.h"

int32 AGeniusPlayerState::GetPlayerScore() const
{
    return GetScore();
}

void AGeniusPlayerState::SetPlayerScore(int32 NewScore)
{
    SetScore(NewScore);
}

void AGeniusPlayerState::AddScore(int32 Amount)
{
    // 점수 증가
    SetScore(GetScore() + Amount);
}

void AGeniusPlayerState::OnRep_Score()
{
    if (GetWorld()->GetGameState<AMainGameStateBase>())
    {
        AMainGameStateBase* MainGameState = GetWorld()->GetGameState<AMainGameStateBase>();
        MainGameState->OnRep_PlayingPlayers();
    }
}

//void AGeniusPlayerState::OnRep_Score()
//{
//    if (GetWorld()->GetGameState<AMainGameStateBase>())
//    {
//        AMainGameStateBase* MainGameState = GetWorld()->GetGameState<AMainGameStateBase>();
//
//        if (MainGameState)
//        {
//            FTimerHandle TimerHandle;
//            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [MainGameState]()
//                {
//                    MainGameState->OnRep_PlayingPlayers();
//                }, 2.0f, false); // 2초 후 호출
//        }
//    }
//}


void AGeniusPlayerState::OnRep_GarnetCount()
{
    // 클라이언트 측에서 2초 후에 위젯을 업데이트하도록 타이머 설정
    APlayerController* PC = GetPlayerController();
    if (PC)
    {
        // 일정 시간 대기 후 위젯 업데이트
        FTimerHandle TimerHandle;
        PC->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PC]()
            {
                AMainGameHUD* MainHUD = PC->GetHUD<AMainGameHUD>();
                if (MainHUD)
                {
                    UMainGameWidget* MainWidget = MainHUD->GetMainGameWidget();
                    if (MainWidget)
                    {
                        MainWidget->UpdateGarnetCount();
                    }
                }
            }, 0.1f, false); // 딜레이 없으면 업데이트 안됨
    }
}


void AGeniusPlayerState::AddGarnetCount(int32 GarnetAmount)
{
    SetGarnetCount(GetGarnetCount() + GarnetAmount);
}

int32 AGeniusPlayerState::GetGarnetCount() const
{
    return GarnetCount;
}

void AGeniusPlayerState::SetGarnetCount(int32 NewGarnetCount)
{
    GarnetCount = NewGarnetCount;
    OnRep_GarnetCount();
}

void AGeniusPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGeniusPlayerState, PlayerName);
    DOREPLIFETIME(AGeniusPlayerState, GarnetCount);
}
