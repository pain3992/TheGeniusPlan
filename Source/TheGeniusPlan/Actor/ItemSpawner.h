// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheGeniusPlan/Actor/Booster.h"
#include "TheGeniusPlan/Actor/Coin.h"
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
	TArray<TSubclassOf<AActor>> ItemClass;

	UPROPERTY()
	TSubclassOf<ABooster> BoosterClass;

	// Reference to the Coin Blueprint
	UPROPERTY()
	TSubclassOf<ACoin> CoinClass;

	// 랜덤으로 아이템을 생성하는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnRandomActor();

	// 아이템 리스폰까지의 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float RespawnTime = 10.0f;

	UFUNCTION()
	void OnItemDestroyed(AActor* DestroyedActor);


protected:
	FVector SpawnLocation;

private:
	// Function to respawn the actor after a delay
	void Respawn();
	
	FTimerHandle TimerHandle;

};
