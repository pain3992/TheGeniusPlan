// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GyulhapData.generated.h"

/**
 * 
 */
UCLASS()
class THEGENIUSPLAN_API UGyulhapData : public UObject
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gyulhap")
	UTexture2D* Image;

	UPROPERTY(BlueprintReadWrite, Category = "Gyulhap Data")
	int32 ItemNumber;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gyulhap")
	FString Shape;  // 도형의 모양 (예: "Circle", "Square", "Triangle")

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gyulhap")
	FString BackgroundColor;  // 배경 색상 (예: "Red", "Green", "Blue")

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gyulhap")
	FString ShapeColor;  // 도형 색상 (예: "Red", "Green", "Blue")
	
};
