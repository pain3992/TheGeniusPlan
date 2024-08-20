// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class THEGENIUSPLAN_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> CoinClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> BoosterClass;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnRandomActor();


	//// 스폰 영역 (Min~Max)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	//FVector SpawnAreaMin;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	//FVector SpawnAreaMax;

	//// 스폰 간격 정의
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	//float SpawnInterval;

private:
	//void SpawnItem();
	//FTimerHandle SpawnTimerHandle;

protected:
	FVector SpawnLocation;

};
