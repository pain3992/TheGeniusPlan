// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameModeBase.h"
#include "EatCoinGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEatCoinGameMode : public AMainGameModeBase
{
	GENERATED_BODY()


public:

    AEatCoinGameMode();

    // 부스트 아이템 지속 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    float BoostDuration = 10.0f;

    // 부스트 아이템 습득 시 증가 속도 (2배)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    float SpeedMultiplier = 2.0f;

    // Function to apply speed boost to the player
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void ApplySpeedBoost(ACharacter* PlayerCharacter);


protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle BoostTimerHandle;

    // 부스트가 적용된 상태인지 체크
    bool bIsBoostActive = false;

    // 기본 속도(BP_ThirdPerson Max Walk Speed 참고)
    float OriginalSpeed = 500.0f;
};
