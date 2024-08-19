// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/GyulhapItemWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "TheGeniusPlan/Data/GyulhapData.h"

void UGyulhapItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (UGyulhapData* GyulhapData = Cast<UGyulhapData>(ListItemObject))
	{
		SetImage(GyulhapData->Image);
		SetItemNumber(GyulhapData->ItemNumber);
	}
	else
	{
		// If ListItemObject is not valid or not of the expected type, log a warning
		UE_LOG(LogTemp, Warning, TEXT("ListItemObject is not of type UGyulhapData."));
	}
}

void UGyulhapItemWidget::SetImage(UTexture2D* NewImage)
{
	if (GyulhapImage)
	{
		// 이미지를 UImage에 설정
		GyulhapImage->SetBrushFromTexture(NewImage);
		UE_LOG(LogTemp, Log, TEXT("SetImage called with: %s"), *NewImage->GetName());
	}
	else
	{
		// GyulhapImage가 유효하지 않으면 경고 로그
		UE_LOG(LogTemp, Warning, TEXT("GyulhapImage is nullptr"));
	}
}

void UGyulhapItemWidget::SetItemNumber(int32 Number)
{
	if (Text_GyulhapNumber)
	{
		Text_GyulhapNumber->SetText(FText::AsNumber(Number));
		UE_LOG(LogTemp, Log, TEXT("SetItemNumber called with: %d"), Number);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Text_GyulhapNumber is nullptr"));
	}
}
