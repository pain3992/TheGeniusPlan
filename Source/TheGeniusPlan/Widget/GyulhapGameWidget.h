// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TileView.h"
#include "TheGeniusPlan/GameModes/GyulhapGameState.h"
#include "TheGeniusPlan/Widget/GyulhapItemWidget.h"
#include "GyulhapGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UGyulhapGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Gyulhap")
	void UpdateGyulhapList(const TArray<UTexture2D*>& SelectedImages);


protected:
	virtual void NativeConstruct() override;

	// 타일뷰를 참조
	UPROPERTY(meta = (BindWidget))
	class UTileView* TileView_Gyulhap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gyulhap")
	TSubclassOf<class UGyulhapItemWidget> GyulhapItemWidgetClass;

	// 버튼 합
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Hap;

	UFUNCTION()
	void OnHapButtonClicked();

	// 버튼 결
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Gyul;

	UFUNCTION()
	void OnGyulButtonClicked();


private:
	TArray<int32> SelectedIndices; // 선택된 이미지의 인덱스를 추적
	bool bIsSelectionModeActive = false; // 이미지 선택 모드 활성화 여부

	void OnItemClicked(UObject* ListItem);

	void VerifySelectedImages();

};
