// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Booster.generated.h"

UCLASS()
class THEGENIUSPLAN_API ABooster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABooster();

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

    UFUNCTION(Server, Reliable)
    void HandleGetBooster(AActor* GotBoosterPlayer);

    // Overlap event
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    FVector InitialLocation; // 초기 위치 저장
    float RunningTime; // 시간 누적 변수
    float FloatSpeed; // 부스터가 움직이는 속도
    float FloatAmplitude; // 부스터가 이동할 최대 높이
};
