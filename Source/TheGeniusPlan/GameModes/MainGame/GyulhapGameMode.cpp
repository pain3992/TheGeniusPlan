// Fill out your copyright notice in the Description page of Project Settings.


//#include "TheGeniusPlan/GameModes/GyulhapGameMode.h"
#include "TheGeniusPlan/GameModes/MainGame/GyulhapGameMode.h"
#include "TheGeniusPlan/GameModes/GyulhapGameState.h"
#include "Engine/Texture2D.h"
#include "TheGeniusPlan/Data/GyulhapData.h"
#include "Kismet/KismetMathLibrary.h"


void AGyulhapGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Current Game Mode: %s"), *GetClass()->GetName());

    SelectRandomImages();
}

void AGyulhapGameMode::ProcessSelectedImages(const TArray<UTexture2D*>& SelectedImages)
{
    if (SelectedImages.Num() != 3)
    {
        UE_LOG(LogTemp, Error, TEXT("선택된 이미지의 수가 3개가 아닙니다."));
        return;
    }

    CheckHap(SelectedImages, nullptr); // Player는 여기서는 사용하지 않으므로 nullptr로 설정
}

void AGyulhapGameMode::CheckHap(const TArray<UTexture2D*>& SelectedImages, APlayerController* Player)
{
    if (SelectedImages.Num() != 3)
    {
        UE_LOG(LogTemp, Error, TEXT("CheckHap: 선택된 이미지의 수가 3개가 아닙니다."));
        return;
    }

    TArray<FGyulhapImageProperties> Properties;
    for (UTexture2D* Image : SelectedImages)
    {
        if (ImagePropertiesMap.Contains(Image))
        {
            Properties.Add(*ImagePropertiesMap.Find(Image));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("CheckHap: 이미지 속성을 찾을 수 없습니다."));
            return;
        }
    }

    bool bShapesMatch = (Properties[0].Shape == Properties[1].Shape && Properties[1].Shape == Properties[2].Shape) ||
        (Properties[0].Shape != Properties[1].Shape && Properties[1].Shape != Properties[2].Shape && Properties[0].Shape != Properties[2].Shape);

    bool bBackgroundColorsMatch = (Properties[0].BackgroundColor == Properties[1].BackgroundColor && Properties[1].BackgroundColor == Properties[2].BackgroundColor) ||
        (Properties[0].BackgroundColor != Properties[1].BackgroundColor && Properties[1].BackgroundColor != Properties[2].BackgroundColor && Properties[0].BackgroundColor != Properties[2].BackgroundColor);

    bool bShapeColorsMatch = (Properties[0].ShapeColor == Properties[1].ShapeColor && Properties[1].ShapeColor == Properties[2].ShapeColor) ||
        (Properties[0].ShapeColor != Properties[1].ShapeColor && Properties[1].ShapeColor != Properties[2].ShapeColor && Properties[0].ShapeColor != Properties[2].ShapeColor);

    bool bIsHap = bShapesMatch && bBackgroundColorsMatch && bShapeColorsMatch;

    if (bIsHap)
    {
        UE_LOG(LogTemp, Warning, TEXT("합이 성립했습니다!"));
        // 플레이어에게 점수 추가 로직
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("합이 성립하지 않았습니다."));
        // 플레이어에게 점수 감점 로직
    }
}

void AGyulhapGameMode::SelectRandomImages()
{
    TArray<UTexture2D*> SelectedImages;

    if (AllImages.Num() < 9)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough images to select 9 random ones."));
        return;
    }

    // 임의로 9개의 이미지를 선택 (중복되지 않도록)
    for (int32 i = 0; i < 9; ++i)
    {
        int32 Index = UKismetMathLibrary::RandomIntegerInRange(0, AllImages.Num() - 1);
        SelectedImages.Add(AllImages[Index]);
        AllImages.RemoveAt(Index);  // 중복 방지를 위해 선택된 이미지를 제거
    }

    // 선택된 이미지를 GameState로 전달
    AGyulhapGameState* GyulhapGameState = GetGameState<AGyulhapGameState>();
    if (GyulhapGameState)
    {
       GyulhapGameState->SetSelectedImages(SelectedImages);
       UE_LOG(LogTemp, Warning, TEXT("GameState로 전달됨."));
    }

}
