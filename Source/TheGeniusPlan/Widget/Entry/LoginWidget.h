// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"


/**
 *
 */
UCLASS()
class THEGENIUSPLAN_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ClickedLogin();

	UFUNCTION(BlueprintCallable)
	void ClickedQuit();

	UFUNCTION(BlueprintCallable)
	void ClickedSignUp();

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TObjectPtr<class AEntryHUD> EntryHUD;

	// 로그인 위젯 입력값 (ID, Password) 초기화
	void Reset() const;

protected:
	void OnHttpResponse(bool bWasSuccessful, TSharedPtr<FJsonObject> JsonResponse, const FString& ErrorMessage);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonLogin;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonSignUp;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonQuit;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableTextLoginID;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableTextLoginPassword;
};
