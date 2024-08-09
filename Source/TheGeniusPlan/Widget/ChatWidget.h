// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatWidget.generated.h"


UCLASS()
class THEGENIUSPLAN_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void FocusChatWidget();

	UFUNCTION()
	void UnFocusChatWidget();

	UFUNCTION()
	void ScrollChat(uint8 bIsUp);

	UFUNCTION()
	void AddMyChatMessage(const FString &Message, uint8 Type);

	UFUNCTION()
	void ClearChatWidget();

	UFUNCTION()
	void EnterToEditableTextBox(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY()
	uint8 ChatRoomType;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableTextBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UScrollBox> ScrollBox;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<class UChatComponent> MyChatComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	uint8 bIsFocus;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ScrollMultiplier;

};
