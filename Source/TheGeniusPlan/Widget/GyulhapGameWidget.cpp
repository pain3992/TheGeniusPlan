// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Widget/GyulhapGameWidget.h"
#include "TheGeniusPlan/Data/GyulhapData.h"
#include "TheGeniusPlan/GameModes/MainGame/GyulhapGameMode.h"
#include "Components/Button.h"

void UGyulhapGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
    UE_LOG(LogTemp, Warning, TEXT("결합 위젯 호출."));

    AGyulhapGameState* GyulhapGameState = GetWorld() ? GetWorld()->GetGameState<AGyulhapGameState>() : nullptr;

    if (GyulhapGameState)
    {
        const TArray<UTexture2D*>& SelectedImages = GyulhapGameState->GetSelectedImages();

      
        UpdateGyulhapList(SelectedImages);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GyulhapGameState is null."));
    }

    // '합' 버튼 클릭 이벤트 바인딩
    if (Button_Hap)
    {
        Button_Hap->OnClicked.AddDynamic(this, &UGyulhapGameWidget::OnHapButtonClicked);
    }

    // TileView 아이템 클릭 이벤트 바인딩
    if (TileView_Gyulhap)
    {
        TileView_Gyulhap->OnItemClicked().AddUObject(this, &UGyulhapGameWidget::OnItemClicked);
    }

    // 초기화된 상태로 시작
    bIsSelectionModeActive = false;
    SelectedIndices.Empty();

}

void UGyulhapGameWidget::UpdateGyulhapList(const TArray<UTexture2D*>& SelectedImages)
{
    if (TileView_Gyulhap == nullptr || GyulhapItemWidgetClass == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("TileView_Gyulhap or GyulhapItemWidgetClass is not assigned."));
        return;
    }

    TArray<UGyulhapData*> GyulhapDataArray;

    for (int32 i = 0; i < SelectedImages.Num(); ++i)
    {
        UTexture2D* Image = SelectedImages[i];
        if (Image)
        {
            UGyulhapData* GyulhapData = NewObject<UGyulhapData>(this);
            GyulhapData->Image = Image;
            GyulhapData->ItemNumber = i + 1; // 아이템 번호는 1부터 시작

            GyulhapDataArray.Add(GyulhapData);
        }
    }

    TileView_Gyulhap->ClearListItems();

    for (UGyulhapData* Data : GyulhapDataArray)
    {
        TileView_Gyulhap->AddItem(Data);
    }

    TileView_Gyulhap->RequestRefresh();
}


void UGyulhapGameWidget::OnHapButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("합 버튼 눌림."));
    // '합' 버튼이 눌리면 이미지 선택 모드를 활성화
    bIsSelectionModeActive = true;
    SelectedIndices.Empty(); // 선택된 이미지를 초기화
}

void UGyulhapGameWidget::OnGyulButtonClicked()
{
}

void UGyulhapGameWidget::OnItemClicked(UObject* ListItem)
{
    if (bIsSelectionModeActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("아이템 클릭1"));
        // 선택 모드가 활성화된 상태에서 이미지가 클릭되면 인덱스를 추적
        UGyulhapData* GyulhapData = Cast<UGyulhapData>(ListItem);
        if (GyulhapData && SelectedIndices.Num() < 3)
        {
            UE_LOG(LogTemp, Warning, TEXT("아이템 클릭2"));
            SelectedIndices.Add(GyulhapData->ItemNumber);

            // 3개의 이미지를 선택하면 검증 로직 호출
            if (SelectedIndices.Num() == 3)
            {
                UE_LOG(LogTemp, Warning, TEXT("아이템 클릭3"));
                VerifySelectedImages();
            }
        }
    }
}

void UGyulhapGameWidget::VerifySelectedImages()
{
    UE_LOG(LogTemp, Warning, TEXT("선택된 이미지 게임 모드로 전달."));
    // 선택된 이미지의 인덱스를 GameMode에 전달하여 검증하도록 함
    AGyulhapGameMode* GameMode = Cast<AGyulhapGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        TArray<UTexture2D*> SelectedImages;
        for (int32 Index : SelectedIndices)
        {
            UGyulhapData* Data = Cast<UGyulhapData>(TileView_Gyulhap->GetItemAt(Index - 1));
            if (Data && Data->Image)
            {
                SelectedImages.Add(Data->Image);
            }
        }

        GameMode->CheckHap(SelectedImages, GetOwningPlayer());

        // 이미지 선택 모드를 비활성화
        bIsSelectionModeActive = false;
        SelectedIndices.Empty();
    }
}