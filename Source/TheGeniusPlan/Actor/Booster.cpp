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

    // Set initial values for floating movement
    FloatSpeed = 5.0f; // 부스터의 상승/하강 속도
    FloatAmplitude = 15.0f; // 부스터의 최대 상승 높이
    RunningTime = 0.0f; // 시간 누적 초기화
}

// Called when the game starts or when spawned
void ABooster::BeginPlay()
{
	Super::BeginPlay();

    // 초기 위치 저장
    InitialLocation = GetActorLocation();	
}

// Called every frame
void ABooster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 시간 누적
    RunningTime += DeltaTime;

    // 새로운 위치 계산 (sine 함수를 사용하여 부드럽게 위아래로 움직임)
    FVector NewLocation = InitialLocation;
    NewLocation.Z += FMath::Sin(RunningTime * FloatSpeed) * FloatAmplitude;

    // 부스터 위치 설정
    SetActorLocation(NewLocation);
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

void ABooster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        HandleGetBooster(OtherActor);
        Destroy();
    }
}

