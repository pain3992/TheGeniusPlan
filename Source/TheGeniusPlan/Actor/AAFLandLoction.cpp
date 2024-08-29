// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFLandLoction.h"

// Sets default values
AAAFLandLoction::AAAFLandLoction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	LandType = ELandType::None;

}

// Called when the game starts or when spawned
void AAAFLandLoction::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAFLandLoction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

