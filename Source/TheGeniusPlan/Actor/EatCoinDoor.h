// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "EatCoinDoor.generated.h"

UCLASS()
class THEGENIUSPLAN_API AEatCoinDoor : public AActor
{
	GENERATED_BODY()
	
public:
    AEatCoinDoor();

    UFUNCTION()
    void StartOpening();  // 문을 여는 함수

    UFUNCTION()
    void StartClosing();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    FVector InitialLocation;  // 시작할 때 문의 위치 (문을 닫을 때 참고할 위치)
    FVector TargetLocation;   // 문이 열릴 위치를 저장합니다.

    FTimerHandle DoorOpeningTimerHandle;  // 문을 여는 타이머 핸들러
    FTimerHandle DoorClosingTimerHandle;  // 문을 닫는 타이머 핸들러
    FTimerHandle DoorOpenWaitHandle;      // 문이 열린 상태에서 대기하는 타이머 핸들러

    void OpenDoorStep();  // 문이 열리는 단계별로 호출될 함수
    void CloseDoorStep(); // 문이 닫히는 단계별로 호출될 함수
};