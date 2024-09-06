// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AAFGameFloor.generated.h"

UCLASS()
class THEGENIUSPLAN_API AAAFGameFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAAFGameFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeMaterial();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> BoxCollision;

	UFUNCTION()
	void DestroyBox();

	FTimerHandle TimerHandleGameActor;

	UFUNCTION()
	void BindDispatcher();

	UFUNCTION()
	void GameStepChange(EGameStep NewStep);

	FTimerHandle TimerHandletwo;

	UFUNCTION()
	void RequestSetCollision();
	UFUNCTION(Server, Reliable)
	void ResponseSetCollision();
	UFUNCTION(NetMulticast, Reliable)
	void MuliticastSetCollision();

};
