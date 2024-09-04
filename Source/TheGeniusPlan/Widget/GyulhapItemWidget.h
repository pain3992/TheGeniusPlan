// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GyulhapItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UGyulhapItemWidget : public UUserWidget , public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* GyulhapImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Text_GyulhapNumber;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* GyulhapButton;

	UFUNCTION(BlueprintCallable, Category = "Gyulhap Widget")
	void SetImage(UTexture2D* NewImage);

	UFUNCTION(BlueprintCallable, Category = "Gyulhap Widget")
	void SetItemNumber(int32 Number);	
};
