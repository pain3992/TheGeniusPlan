// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/GyulhapGameState.h"
#include "TheGeniusPlan/Widget/GyulhapGameWidget.h"
#include "Net/UnrealNetwork.h"

void AGyulhapGameState::SetSelectedImages(const TArray<UTexture2D*>& Images)
{
	SelectedImages = Images;

	// Replication을 통해 모든 클라이언트에서 OnRep_SelectedImages를 호출
	if (HasAuthority())
	{
		OnRep_SelectedImages();
	}
}

void AGyulhapGameState::OnRep_SelectedImages()
{
	/*if (GyulhapGameWidget)
	{
	    GyulhapGameWidget->UpdateGyulhapList(SelectedImages);
	}*/
}

//bool AGyulhapGameState::AddSelectedHap(const TArray<UTexture2D*>& SelectedHap)
//{
//    for (const TArray<UTexture2D*>& ExistingHap : SelectedHaps)
//    {
//        // 정렬 후 비교
//        TArray<UTexture2D*> SortedExistingHap = ExistingHap;
//        TArray<UTexture2D*> SortedSelectedHap = SelectedHap;
//
//        SortedExistingHap.Sort();
//        SortedSelectedHap.Sort();
//
//        if (SortedExistingHap == SortedSelectedHap)
//        {
//            return false; // 이미 존재하는 합
//        }
//    }
//
//    // 새로 추가된 합을 기록
//    SelectedHaps.Add(SelectedHap);
//    return true;
//}

void AGyulhapGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// SelectedImages 배열을 복제 대상으로 설정
	DOREPLIFETIME(AGyulhapGameState, SelectedImages);
  //  DOREPLIFETIME(AGyulhapGameState, SelectedHaps);
}
