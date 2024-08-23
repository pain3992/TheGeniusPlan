// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "GyulhapGameState.generated.h"

class UTexture2D;

UCLASS()
class THEGENIUSPLAN_API AGyulhapGameState : public AMainGameStateBase
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Gyulhap")
    const TArray<UTexture2D*>& GetSelectedImages() const { return SelectedImages; }

    // 선택된 이미지를 배열로 저장하는 함수
    void SetSelectedImages(const TArray<UTexture2D*>& Images);

    // 선택된 이미지가 변경되었을 때 호출되는 함수
    UFUNCTION()
    void OnRep_SelectedImages();

    // 새로운 합 추가 및 이미 선택된 합인지 확인하는 함수
//    bool AddSelectedHap(const TArray<UTexture2D*>& SelectedHap);

    // 게임 위젯에 접근하기 위한 참조
    UPROPERTY()
    class UGyulhapGameWidget* GyulhapGameWidget;

protected:
    // 선택된 이미지 배열
    UPROPERTY(ReplicatedUsing = OnRep_SelectedImages, BlueprintReadOnly, Category = "Gyulhap")
    TArray<UTexture2D*> SelectedImages;


private:
    // UPROPERTY(Replicated, BlueprintReadOnly, Category = "Gyulhap", meta = (AllowPrivateAccess = "true"))
   // TArray<TArray<FGyulhapImageProperties>> SelectedHaps;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
