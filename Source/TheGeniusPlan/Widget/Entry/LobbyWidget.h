// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
    TObjectPtr<class AEntryHUD> EntryHUD;

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

	UFUNCTION()
	void UpdateLoginInfo(const FLoginInfo& LoginInfo);

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

	// TextBox 닉네임
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextProfileName;
	
	// TextBox 전적
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextProfileStatistics;
	
	// TextBox 랭킹
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextProfileRanking;

};
