// Fill out your copyright notice in the Description page of Project Settings.

#include "TheGeniusPlan/Actor/Coin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TheGeniusPlan/GameModes/MainGameStateBase.h"
#include "TheGeniusPlan/GameModes/MainGameModeBase.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameState.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "TheGeniusPlan/Player/EatCoinPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

// Sets default values
ACoin::ACoin()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    // 코인의 스피어 컴포넌트
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(50.0f);
    SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // 코인의 스태틱 메쉬
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

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

void ACoin::handleGetCoin_Implementation(AActor *GotCoinPlayer)
{
    ACharacter *Character = Cast<ACharacter>(GotCoinPlayer);
    if (IsValid(Character) == false)
        return;

    /*APlayerController *PlayerController = Cast<APlayerController>(Character->GetController());
    if (PlayerController)
    {
        AGeniusPlayerState *PlayerState = PlayerController->GetPlayerState<AGeniusPlayerState>();
        if (PlayerState)
        {
            AMainGameModeBase *GameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
            if (GameMode)
            {
                GameMode->AddCoinScore(PlayerState, 50);
            }
        }
    }*/

    APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
    if (PlayerController)
    {
        AEatCoinPlayerState* EatCoinPlayerState = PlayerController->GetPlayerState<AEatCoinPlayerState>();
        if (EatCoinPlayerState)
        {
            AEatCoinGameMode* EatCoinGameMode = Cast<AEatCoinGameMode>(GetWorld()->GetAuthGameMode());
            if (EatCoinGameMode)
            {
                EatCoinGameMode->AddCoinScoreRule(EatCoinPlayerState, 50);
            }
        }
    }
}

void ACoin::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        handleGetCoin(OtherActor);
        Destroy();
    }
}