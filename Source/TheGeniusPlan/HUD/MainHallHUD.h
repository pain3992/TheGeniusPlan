// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHallHUD.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AMainHallHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
    // 블루프린트에서 만든 위젯 클래스의 참조를 저장하기 위한 UPROPERTY
    UPROPERTY(EditAnywhere, Category = "HUD")
    TSubclassOf<class UUserWidget> HUDWidgetClass;

private:
    // 화면에 추가된 위젯의 인스턴스를 저장하기 위한 포인터
    UUserWidget* CurrentWidget;
	
};
