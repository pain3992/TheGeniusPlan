// Fill out your copyright notice in the Description page of Project Settings.


#include "AAFGameFloor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TheGeniusPlan/GameModes/MainGame/AAFGameState.h"

// Sets default values
AAAFGameFloor::AAAFGameFloor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Mesh(TEXT("/Script/Engine.StaticMesh'/Game/SeongWon/Floor.Floor'"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 80.0f));
	SetRootComponent(Mesh);
	BoxCollision->SetupAttachment(Mesh);
	BoxCollision->SetRelativeLocation(FVector(50.0f, 50.0f, 80.0f));
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);

	if (SM_Mesh.Succeeded())
	{
		Mesh->SetStaticMesh(SM_Mesh.Object);
	}

	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAAFGameFloor::OverlapEvent);
	}

}

// Called when the game starts or when spawned
void AAAFGameFloor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAAFGameFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAAFGameFloor::OverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* OverlapCharacter = Cast<ACharacter>(OtherActor);

	if (OverlapCharacter)
	{
		ChangeMaterial();
		GetWorld()->GetTimerManager().SetTimer(TimerHandleGameActor, this, &AAAFGameFloor::DestroyBox, 4.0f, false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("1"));
	}
}

void AAAFGameFloor::DestroyBox()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AAAFGameFloor::BindDispatcher()
{
	AAAFGameState* CastGameState = Cast<AAAFGameState>(GetWorld()->GetGameState());

	if (CastGameState)
	{
		if (!CastGameState->EventDisptacherGameStepChange.IsBound())
		{
			CastGameState->EventDisptacherGameStepChange.AddDynamic(this, &AAAFGameFloor::GameStepChange);
			UE_LOG(LogTemp, Error, TEXT("Bind Success"));
		}

		GetWorld()->GetTimerManager().ClearTimer(TimerHandletwo);
		return;
	}


	FTimerManager& timerManger = GetWorld()->GetTimerManager();
	timerManger.SetTimer(TimerHandletwo, this, &AAAFGameFloor::BindDispatcher, 0.1f, false);
}

void AAAFGameFloor::GameStepChange(EGameStep NewStep)
{
	switch (NewStep)
	{
	case EGameStep::RoundStart:
		RequestSetCollision();
		break;
	default:
		break;
	}
}

void AAAFGameFloor::RequestSetCollision()
{
	ResponseSetCollision();
}

void AAAFGameFloor::ResponseSetCollision_Implementation()
{
	MuliticastSetCollision();
}

void AAAFGameFloor::MuliticastSetCollision_Implementation()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

