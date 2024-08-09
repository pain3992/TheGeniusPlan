// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/GameModes/MainGame/GyulhapGameMode.h"

void AGyulhapGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Current Game Mode: %s"), *GetClass()->GetName());
}
