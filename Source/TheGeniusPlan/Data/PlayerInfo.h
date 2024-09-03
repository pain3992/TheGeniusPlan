#pragma once

// 유저 로그인 정보
USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "PlayerInfo")
	int32 ID;

	UPROPERTY(BlurprintReadWrite, Category = "PlayerInfo")
	FString LoginID;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerInfo")
	FString Username;
};