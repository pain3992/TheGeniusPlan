// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"
#include "ChangeGameModeWidget.generated.h"

/**
 * @description THEG-27 게임모드 변경 테스트를 위한 위젯
 * @link https://devilofdev.atlassian.net/browse/THEG-27?atlOrigin=eyJpIjoiZGE5YjM4OThiMTZiNDZiMjk2Yzg0OTRiY2Q4YmZjNGEiLCJwIjoiaiJ9
 */
UCLASS()
class THEGENIUSPLAN_API UChangeGameModeWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> ChangeGameModeButton;


public:
	UFUNCTION()
	void OnChangeGameModeButtonClicked();

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	TObjectPtr<AMainGameHUD> MainGameHUD;
};
