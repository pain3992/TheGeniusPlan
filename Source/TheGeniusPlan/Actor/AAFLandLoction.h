// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AAFLandLoction.generated.h"

UENUM()
enum class ELandType : uint8
{
	None UMETA(Displayname = "None"),
	AbundanceLand UMETA(Displayname = "Abundance"),
	FamineLand UMETA(Displayname = "FamineLand"),

};

UCLASS()
class THEGENIUSPLAN_API AAAFLandLoction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAAFLandLoction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LandType")
	ELandType LandType;

};
