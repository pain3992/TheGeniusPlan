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
};

USTRUCT(BlueprintType)
struct FLoginInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	bool bIsLoggedIn;

	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	FString LoginID;

	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 ID;

	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	FString UserName;

	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 Ranking;

	UPROPERTY(BlueprintReadWrite, Category = "LoginInfo")
	int32 Score;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoginInfoUpdated, const FLoginInfo&, LoginInfo);

UCLASS()
class THEGENIUSPLAN_API UGeniusGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	ESelectedLand GI_SelectedLand;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FLoginInfo LoginInfo;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	TArray<FPlayerScoreData> SavedPlayerScores;

	FOnLoginInfoUpdated OnLoginInfoUpdated;
	void SetLoginInfo(const FLoginInfo& NewLoginInfo);
};
