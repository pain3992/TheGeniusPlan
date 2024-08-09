// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChatRoomActor.generated.h"

UENUM()
enum class RoomType : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	WaitingRoom UMETA(DisplayName = "WaitingRoom"),
	StudyRoom UMETA(DisplayName = "StudyRoom"),

};

UCLASS()
class THEGENIUSPLAN_API AChatRoomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChatRoomActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoomType")
	RoomType thisRoomType;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<class UBoxComponent> BoxCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
