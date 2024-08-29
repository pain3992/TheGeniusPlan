// Fill out your copyright notice in the Description page of Project Settings.


#include "EndPlayerState.h"
#include "Net/UnrealNetwork.h"

void AEndPlayerState::BeginPlay()
{
	PlayerNumber = 0;

	UE_LOG(LogTemp, Error, TEXT("First Number : %d"), PlayerNumber);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEndPlayerState::PrintInstanceNumber, 5.0f, false);
}

void AEndPlayerState::PrintInstanceNumber()
{
	UE_LOG(LogTemp, Error, TEXT("Second Number : %d"), PlayerNumber);
}

void AEndPlayerState::PlayerStateNumberSet(uint8 NewNumber)
{
	PlayerNumber = NewNumber;
}

void AEndPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEndPlayerState, PlayerNumber);
}
