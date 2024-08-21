// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Actor/ItemSpawner.h"
#include "Engine/World.h"
#include "TheGeniusPlan/Actor/Booster.h"
#include "TheGeniusPlan/Actor/Coin.h"
#include "TimerManager.h"

AItemSpawner::AItemSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

    if (HasAuthority())
    {
        SpawnLocation = GetActorLocation();

        // 서버일 경우에만 아이템을 스폰
        SpawnRandomActor();
    }
	
}

void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnRandomActor()
{
    if (ItemClass.Num() == 0)  // 배열이 비어있는지 확인
    {
        UE_LOG(LogTemp, Error, TEXT("ItemClass 배열이 비어 있습니다."));
        return;
    }

    // 배열에서 랜덤으로 아이템 클래스를 선택
    int32 RandomIndex = FMath::RandRange(0, ItemClass.Num() - 1);
    TSubclassOf<AActor> ActorToSpawn = ItemClass[RandomIndex];

    // 스폰할 위치와 회전값 설정
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // Spawn the actor at the spawner's location
    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

    if (SpawnedActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("아이템 정상 스폰: %s"), *SpawnedActor->GetName());
        SpawnedActor->OnDestroyed.AddDynamic(this, &AItemSpawner::OnItemDestroyed);
    }
}


void AItemSpawner::OnItemDestroyed(AActor* DestroyedActor)
{
    if (HasAuthority())
    {
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AItemSpawner::Respawn, RespawnTime, false);
    }
}

void AItemSpawner::Respawn()
{
    if (HasAuthority())
    {
        SpawnRandomActor();
    }
}