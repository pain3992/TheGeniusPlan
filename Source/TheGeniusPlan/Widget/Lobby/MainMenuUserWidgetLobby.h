// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidgetLobby.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UMainMenuUserWidgetLobby : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TObjectPtr<class AMainMenuHUD> LobbyMenuHUD;

	UFUNCTION()
	void ChangeCharacterMesh();

	UFUNCTION()
	void ClickedJoinServer();

	UFUNCTION()
	void ClickedQuit();

	UFUNCTION()
	void ClickedLogout();

	UFUNCTION()
	void ClickedOption();

	UFUNCTION()
	void ClickedCreate();


protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonLeft;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonRight;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonQuit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonLogout;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonOption;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonServerJoin;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonServerCreate;
	
};
