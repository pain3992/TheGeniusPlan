// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameModeBase.h"
#include "GyulhapGameMode.generated.h"

UENUM(BlueprintType)
enum class EShape : uint8 // 도형의 모양
{ 
    Star,
    Sun,
    Lightning
};

UENUM(BlueprintType)
enum class EBackgroundColor : uint8 // 배경 색상
{
    Black,
    Grey,
    White
};

UENUM(BlueprintType)
enum class EShapeColor : uint8 // 도형 색상
{
    Green,
    Skyblue,
    Purple
};

// 이미지의 속성 구조체
USTRUCT(BlueprintType)
struct FGyulhapImageProperties
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gyulhap")
    EShape Shape;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gyulhap")
    EBackgroundColor BackgroundColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gyulhap")
    EShapeColor ShapeColor;
};


UCLASS()
class THEGENIUSPLAN_API AGyulhapGameMode : public AMainGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Gyulhap")
    void ProcessSelectedImages(const TArray<UTexture2D*>& SelectedImages);

	// 합이 성립하는지 확인
	void CheckHap(const TArray<UTexture2D*>& SelectedImages, APlayerController* Player);

protected:
	// 27장의 이미지를 담은 배열
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gyulhap", meta = (AllowPrivateAccess = "true"))
    TArray<UTexture2D*> AllImages;

private:
	void SelectRandomImages();

    // 이미지 속성 매핑
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gyulhap", meta = (AllowPrivateAccess = "true"))
    TMap<UTexture2D*, FGyulhapImageProperties> ImagePropertiesMap;
};
