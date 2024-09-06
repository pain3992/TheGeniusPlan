// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UGameLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> PlayerCount;

	UFUNCTION()
	void ChangePlayerCount(int32 NewNumber);

	virtual void NativeConstruct() override;

};
