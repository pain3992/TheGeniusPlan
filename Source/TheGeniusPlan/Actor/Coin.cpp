// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Actor/Coin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameStateBase.h"
#include "TheGeniusPlan/GameModes/MainGame/MainGameModeBase.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACoin::ACoin()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create and configure the sphere component
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(50.0f);
    SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // Create and configure the static mesh component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // Set default points to add
    PointsToAdd = 10;

    // Bind overlap event
    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        APlayerController* PlayerController = Cast<APlayerController>(OtherActor->GetInstigatorController());
        if (PlayerController)
        {
            AGeniusPlayerState* PlayerState = PlayerController->GetPlayerState<AGeniusPlayerState>();
            if (PlayerState)
            {
                AMainGameModeBase* GameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
                if (GameMode)
                {
                 //   GameMode->PlayerCollectedCoin(PlayerState);
                }
                Destroy();
            }
        }
    }
}