// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Actor/ItemSpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"

AItemSpawner::AItemSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = GetActorLocation();

	SpawnRandomActor();
	
   // SpawnItem();
}

void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnRandomActor()
{
	if (CoinClass && BoosterClass)
	{
		// Decide which actor to spawn
		TSubclassOf<AActor> ActorToSpawn = FMath::RandBool() ? CoinClass : BoosterClass;

		// Spawn the actor at the spawner's location
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator);
	}
}

//void AItemSpawner::SpawnItem()
//{
//    TSubclassOf<AActor> ItemToSpawn = FMath::RandBool() ? CoinClass : BoosterClass;
//
//    if (ItemToSpawn)
//    {
//        FVector SpawnLocation = FMath::RandPointInBox(FBox(SpawnAreaMin, SpawnAreaMax));
//        FRotator SpawnRotation = FRotator::ZeroRotator;
//
//        GetWorld()->SpawnActor<AActor>(ItemToSpawn, SpawnLocation, SpawnRotation);
//    }
//}

