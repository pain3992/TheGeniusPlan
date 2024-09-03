// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "SignupWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API USignupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ClickedButtonSignup();

	UFUNCTION()
	void ClickedButtonCansel();

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TObjectPtr<class AEntryHUD> EntryHUD;

protected:
	void OnHttpResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonSignup;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonCansel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableLoginID;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableUsername;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditablePassword;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditablePasswordCheck;
};
