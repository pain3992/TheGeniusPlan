// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameModeBase.h"
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

    // 부스트와 오버랩 됐을 때 속도 증가 반영
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void ApplySpeedBoost(ACharacter* PlayerCharacter);

    // 코인과 오버랩 됐을 때 점수 반영
    void AddCoinScoreRule(APlayerState* PlayerState, int32 ScoreAmount);

    virtual void PostLogin(APlayerController* NewPlayer) override;

    virtual void HandleRoundEnd() override;

   // EatCoin 게임시작까지 남은 시간 카운트다운
    void SetECGameStartCountdownRule();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Eat Coin Game Rules", meta = (AllowPrivateAccess = "true"))
    int32 ECGameStartCountdownTimeInSeconds;

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle BoostTimerHandle;

    // 부스트가 적용된 상태인지 체크
    bool bIsBoostActive = false;

    // 기본 속도(BP_ThirdPerson Max Walk Speed 참고)
    float OriginalSpeed = 500.0f;
};
