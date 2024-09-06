// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UEntryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ClickedGameStart();

	UFUNCTION(BlueprintCallable)
	void ClickedOption();

	UFUNCTION(BlueprintCallable)
	void ClickedQuit();

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	TObjectPtr<class AEntryHUD> EntryHUD;

	UPROPERTY()
	TObjectPtr<class ULoginWidget> LoginWidget;
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonGameStart;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonOption;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonQuit;
};
