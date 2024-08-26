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
    void StartOpening();  // 문을 여는 함수를 선언합니다.

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    FVector InitialLocation;  // 문이 시작할 때 위치를 저장합니다.
    FVector TargetLocation;   // 문이 열릴 위치를 저장합니다.

    FTimerHandle DoorOpeningTimerHandle;  // 타이머 핸들러

    void OpenDoorStep();  // 문이 열리는 단계별로 호출될 함수
};