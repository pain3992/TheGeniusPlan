// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameDeadZone.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "TheGeniusPlan/Player/AAFPlayerState.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"
#include "GameFramework/GameState.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameState.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AAAFGameDeadZone::AAAFGameDeadZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	SetRootComponent(BoxCollision);

	if(BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAAFGameDeadZone::OverlapEvent);
	}

	bReplicates = true;
}

// Called when the game starts or when spawned
void AAAFGameDeadZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAFGameDeadZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAAFGameDeadZone::OverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* OverlapActor = Cast<ACharacter>(OtherActor);
	if(OverlapActor)
	{
		AAAFPlayerState* PlayerState = Cast<AAAFPlayerState>(OverlapActor->GetPlayerState());
		PlayerState->Lose = true;
		OverlapActor->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
		CheckWinner();
		UE_LOG(LogTemp, Error, TEXT("Player Lose"));
	}
}

void AAAFGameDeadZone::CheckWinner_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Check"));
	TArray<APlayerState*> GamePlayerState = GetWorld()->GetGameState()->PlayerArray;

	uint8 LivePlayer = 0;

	if(GamePlayerState.Num() > 0)
	{
		for(auto ClientState : GamePlayerState)
		{
			AAAFPlayerState* CastClientState = Cast<AAAFPlayerState>(ClientState);
			if(CastClientState)
			{
				if(CastClientState->Lose == true)
				{
					continue;
				}
				else
				{
					LivePlayer++;
				}
			}
		}

		if(LivePlayer > 1)
		{
			return;
		}
		else if(LivePlayer < 1)
		{

		}
		else
		{
			AAAFGameState* GameState = Cast<AAAFGameState>(GetWorld()->GetGameState());

			if(GameState)
			{
				GameState->SetGameStep(EGameStep::GameEnd);
				UE_LOG(LogTemp, Error, TEXT("Game End"));

			}
		}
	}
}

