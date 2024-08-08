// Fill out your copyright notice in the Description page of Project Settings.
// 습득시 플레이어 점수 증가 - 리스트 선택정렬 테스트를 위해 임의로 만들었습니다 테스트 마친 후에는 지웁니다!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class THEGENIUSPLAN_API ACoin : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACoin();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Collision component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USphereComponent* SphereComponent;

    // Mesh component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* MeshComponent;

    // Points to add on overlap
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    int32 PointsToAdd;

    // Overlap event
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};