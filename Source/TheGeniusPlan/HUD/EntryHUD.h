// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EntryHUD.generated.h"

UENUM()
enum class EntryWidgetType : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	LoginWidget UMETA(DisplayName = "LoginWidget"),
	SignupWidget UMETA(DisplayName = "SignupWidget"),
	EntryWidget UMETA(DisplayName = "EntrynWidget"),
	OptionWidget UMETA(DisplayName = "OptionWidget"),
	LoadingWidget UMETA(DisplayName = "LoadingWidget"),
	LobbyWidget UMETA(DisplayName = "LobbyWidget"),
	MAX UMETA(DisplayName = "MAX")
};

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API AEntryHUD : public AHUD
{
	GENERATED_BODY()
public:
	AEntryHUD();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void ShowWidget(EntryWidgetType type) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class ULoginWidget> LoginWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UEntryWidget> EntryWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class ULobbyWidget> LobbyWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UUserWidget> LoadingWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class USignupWidget> SignupWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UOptionWidget> OptionWidgetClass;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class ULoginWidget> LoginWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class UEntryWidget> EntryWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class UUserWidget> LoadingWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class ULobbyWidget> LobbyWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class USignupWidget> SignupWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class UOptionWidget> OptionWidget;

	FTimerHandle HUDTimerHandle;
};
