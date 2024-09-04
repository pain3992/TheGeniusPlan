// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGeniusPlan/Actor/GyulhapCube.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TheGeniusPlan/TheGeniusPlanCharacter.h"

// Sets default values
AGyulhapCube::AGyulhapCube()
{
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    // Create the Box Component and set it as the root
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;

    // Set collision properties for BoxComponent
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    // Create the static mesh component and attach it to the box
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetupAttachment(BoxComponent);

    // Set collision properties for StaticMeshComponent
    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

    BoxComponent->SetBoxExtent(FVector(80.0f, 80.0f, 80.0f)); // 적절한 크기로 설정

    // Load and add static meshes to the array
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh1(TEXT("StaticMesh'/Game/JiYoung/Gyulhap/StaticMesh/SM_B_Lightning_G.SM_B_Lightning_G'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh2(TEXT("StaticMesh'/Game/JiYoung/Gyulhap/StaticMesh/SM_B_Lightning_P.SM_B_Lightning_P'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh3(TEXT("StaticMesh'/Game/JiYoung/Gyulhap/StaticMesh/SM_B_Lightning_S.SM_B_Lightning_S'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh4(TEXT("StaticMesh'/Game/JiYoung/Gyulhap/StaticMesh/SM_B_Star_G.SM_B_Star_G'"));

    // Add the meshes to the array if they were successfully loaded
    if (Mesh1.Succeeded()) StaticMeshes.Add(Mesh1.Object);
    if (Mesh2.Succeeded()) StaticMeshes.Add(Mesh2.Object);
    if (Mesh3.Succeeded()) StaticMeshes.Add(Mesh3.Object);
    if (Mesh4.Succeeded()) StaticMeshes.Add(Mesh4.Object);
    // Continue for all 27 meshes
    BoxComponent->SetSimulatePhysics(true);
}

void AGyulhapCube::BeginPlay()
{
    Super::BeginPlay();

    SelectRandomMesh();

    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGyulhapCube::OnOverlapBegin);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AGyulhapCube::OnOverlapEnd);
}

void AGyulhapCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGyulhapCube::SelectRandomMesh()
{
    if (StaticMeshes.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, StaticMeshes.Num() - 1);
        UStaticMesh* SelectedMesh = StaticMeshes[RandomIndex];
        if (SelectedMesh)
        {
            StaticMeshComponent->SetStaticMesh(SelectedMesh);

        }
    }
}

void AGyulhapCube::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // You can use this to check if the overlapped actor is the player character
    if (OtherActor && OtherActor != this && OtherComp)
    {
        ATheGeniusPlanCharacter* Character = Cast<ATheGeniusPlanCharacter>(OtherActor);
        if (Character)
        {
        }
    }
}

void AGyulhapCube::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        ATheGeniusPlanCharacter* Character = Cast<ATheGeniusPlanCharacter>(OtherActor);
        if (Character)
        {
        }
    }
}

