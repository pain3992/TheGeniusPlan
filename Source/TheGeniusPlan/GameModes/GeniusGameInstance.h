// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Player/AAFPlayerState.h"
#include "GeniusGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FPlayerScoreData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	int32 Score;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerData")
	int32 GarnetCount;
};

USTRUCT(BlueprintType)
struct FLoginInfo
{
	GENERATED_BODY()

	// 로그인 여부
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	bool bIsLoggedIn;

	// DB에 저장된 ID
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 ID;
	
	// 로그인 ID
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	FString LoginID;

	// 플레이어 닉네임
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	FString UserName;

	// 랭킹
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 Rank;

	// 랭크 포인트
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 RankPoint;

	// 랭크 플레이어 수
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 RankPlayers;

	// 플레이 게임 횟수
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 TotalGame;

	// 승리 횟수
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 TotalWin;
	
	// 승률
	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	float WinRate;
};

// 델리게이트 선언
// 로그인 정보 갱신 시 호출
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginInfoUpdated, const FLoginInfo&, LoginInfo);

UCLASS()
class THEGENIUSPLAN_API UGeniusGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UGeniusGameInstance();

	UPROPERTY()
	ESelectedLand GI_SelectedLand;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FLoginInfo LoginInfo;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	TArray<FPlayerScoreData> SavedPlayerScores;

	FOnLoginInfoUpdated OnLoginInfoUpdated;

	void SetLoginInfo(const FLoginInfo& NewLoginInfo);
	
	UPROPERTY(BlueprintReadWrite, Category = "GameTracking")
	TArray<FString> PlayedGameModes;

	UPROPERTY()
	uint8 Number;

	UFUNCTION()
	void SetWinnerPlayer();

	UFUNCTION()
	void PrintWinnerPlayer();
};
