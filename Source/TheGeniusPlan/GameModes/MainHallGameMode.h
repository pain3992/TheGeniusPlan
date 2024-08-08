// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainHallGameMode.generated.h"

/**
 *
 */
UCLASS()
class THEGENIUSPLAN_API AMainHallGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    AMainHallGameMode();

protected:
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;
};