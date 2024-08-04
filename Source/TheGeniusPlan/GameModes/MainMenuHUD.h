#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

UCLASS()
class THEGENIUSPLAN_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainMenuHUD();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UMainMenuUserWidget> MainMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "WidgetClass")
	TObjectPtr<class UMainMenuUserWidget> MainMenuWidget;

	virtual void BeginPlay() override;

};
