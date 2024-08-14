// Fill out your copyright notice in the Description page of Project Settings.
// 점수 오르는 거 확인하기 위해 임시로 만들었습니다 테스트 완료 후 삭제 예정

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

    UFUNCTION(Server, Reliable)
    void handleGetCoin(AActor *GotCoinPlayer);

    // Overlap event
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};