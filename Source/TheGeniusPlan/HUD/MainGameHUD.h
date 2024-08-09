// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainGameHUD.generated.h"

/**
 * @description 메인 게임모드 HUD, 게임모드 변경위젯을 불러오는 HUD로 제작했으나 MainHall과 통합 검토
 */
UCLASS()
class THEGENIUSPLAN_API AMainGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainGameHUD();

	virtual void BeginPlay() override;

	// 게임모드 전환 테스트용 위젯 클래스
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="WidgetClass")
	TSubclassOf<class UChangeGameModeWidget> ChangeGameModeWidgetClass;

protected:
	// 게임모드 전환 테스트용 위젯
	UPROPERTY(BlueprintReadWrite, Category="Widgets")
	TObjectPtr<class UChangeGameModeWidget> ChangeGameModeWidget;
};
