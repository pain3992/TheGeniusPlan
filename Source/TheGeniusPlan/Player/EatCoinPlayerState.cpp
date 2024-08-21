// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Player/EatCoinPlayerState.h"
#include "TheGeniusPlan/Widget/MainGame/EatCoinWidget.h"
#include "TheGeniusPlan/HUD/EatCoinHUD.h"
#include "GameFramework/HUD.h"
#include "Net/UnrealNetwork.h"

AEatCoinPlayerState::AEatCoinPlayerState()
{
	RemainingBoostTime = 0.0f;
}

void AEatCoinPlayerState::UpdateBoostTime(float DeltaTime)
{
    if (RemainingBoostTime > 0.0f)
    {
        RemainingBoostTime -= DeltaTime;
        if (RemainingBoostTime < 0.0f)
        {
            RemainingBoostTime = 0.0f;
        }
    }
}



void AEatCoinPlayerState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateBoostTime(DeltaTime);

    APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
    if (PlayerController)
    {
        AEatCoinHUD* HUD = PlayerController->GetHUD< AEatCoinHUD>();
        if (HUD)
        {
            UEatCoinWidget* EatCoinWidget = Cast<UEatCoinWidget>(HUD->GetEatCoinWidget());
            if (EatCoinWidget)
            {
               // EatCoinWidget->UpdateBoostTimer(RemainingBoostTime);
            }
        }
    }
}

void AEatCoinPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AEatCoinPlayerState, RemainingBoostTime);
}