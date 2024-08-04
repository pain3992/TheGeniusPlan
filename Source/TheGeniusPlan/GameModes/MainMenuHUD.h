#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

UENUM()
enum class WidgetType : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	LoginWidget UMETA(DisplayName = "LoginWidet"),
	StartWidget UMETA(DisplayName = "StartWidget"),
	LobbyWidget UMETA(DisplayName = "LobbyWidget"),
	OptionWidget UMETA(DisplayName = "OptionWidget"),
	LoadingWidget UMETA(DisplayName = "LoadingWidget"),
	SignupWidget UMETA(DisplayName = "SignupWidget"),
	MAX UMETA(DisplayName = "MAX")
};


UCLASS()
class THEGENIUSPLAN_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainMenuHUD();

	virtual void BeginPlay() override;

	UFUNCTION()
	void ShowWidget(WidgetType type);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UMainMenuUserWidget> LoginWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UMainMenuUserWidgetOption> GameStartWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UMainMenuUserWidgetLobby> LobbyWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UUserWidget> LoadingWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class USignupWidget> SignupWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UOptionWidget> OptionWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UMainMenuUserWidget> MainMenuWidgetClass;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "WidgetClass")
	TObjectPtr<class UMainMenuUserWidget> MainMenuWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class UMainMenuUserWidget> LoginWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class UMainMenuUserWidgetOption> GameStartWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class UUserWidget> LoadingWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class UMainMenuUserWidgetLobby> LobbyWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class USignupWidget> SignupWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<class UOptionWidget> OptionWidget;

	FTimerHandle HUDTimerHandle;

protected:

	virtual void BeginPlay() override;

};
