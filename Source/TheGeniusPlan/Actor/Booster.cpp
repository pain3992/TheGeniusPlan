// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Actor/Booster.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TheGeniusPlan/GameModes/MainGame/EatCoinGameMode.h"
#include "GameFramework/Character.h"
#include "TheGeniusPlan/Player/GeniusPlayerState.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ABooster::ABooster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

    // Create and configure the sphere component
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;
    SphereComponent->InitSphereRadius(50.0f);
    SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // Create and configure the static mesh component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // Bind overlap event
    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABooster::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABooster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABooster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABooster::HandleGetBooster_Implementation(AActor* GotBoosterPlayer)
{
    ACharacter* Character = Cast<ACharacter>(GotBoosterPlayer);
    if (IsValid(Character) == false)
        return;

    APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
    if (PlayerController)
    {
        AGeniusPlayerState* PlayerState = PlayerController->GetPlayerState<AGeniusPlayerState>();
        if (PlayerState)
        {
             AEatCoinGameMode* GameMode = Cast<AEatCoinGameMode>(GetWorld()->GetAuthGameMode());
             if (GameMode)
             {
                 GameMode->ApplySpeedBoost(Character);
             }
        }
    }
}
// Item (AActpr)
//    Booster
//    Coin

// Item (AActor::Destroy)
void ABooster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        HandleGetBooster(OtherActor);
        Destroy();
    }
}

