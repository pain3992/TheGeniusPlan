// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/GameModes/MainGame/MainGameModeBase.h"

#include "GyulhapGameMode.h"
#include "OpenPassGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TheGeniusPlan/HUD/MainGameHUD.h"

AMainGameModeBase::AMainGameModeBase()
{
	TotalRounds = 0;
	CurrentRound = 0;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		HUDClass = AMainGameHUD::StaticClass();
	}
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// 메인 게임모드 시작시, 메인매치 게임 등록 (결합게임 모드, 오픈패스 게임 모드)
	if (PossibleGameModes.Num() == 0)
	{
		PossibleGameModes.Add(AGyulhapGameMode::StaticClass());
		PossibleGameModes.Add(AOpenPassGameMode::StaticClass());
	}
	
}

void AMainGameModeBase::HandleGameStart()
{
}

/**
 * @description 
 */
void AMainGameModeBase::SelectNextGameMode()
{
	/**
	 * 1. 매인매치 게임모드 있을경우 
	 */
	if (PossibleGameModes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, PossibleGameModes.Num() - 1);
		TSubclassOf<AGameMode> SelectedGameMode = PossibleGameModes[RandomIndex];
		
		FString Options = FString::Printf(TEXT("?game=/Script/CoreUObject.Class'/Script/TheGeniusPlan.%s'"), *SelectedGameMode->GetName());
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), true, Options);
	}
}

// void AMainGameModeBase::TransitionToNextRound()
// {
// }
//
// void AMainGameModeBase::HandleRoundEnd()
// {
// }
//
// void AMainGameModeBase::CheckForOverallWinner()
// {
// }
//
//
// void AMainGameModeBase::EndMatch(int32 WinningPlayerId)
// {
// }
