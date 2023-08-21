// MyDoor.cpp

#include "MyDoor.h"

AMyDoor::AMyDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;
    OpenAngle = 90.0f;
    OpeningSpeed = 90.0f;
    OpenHeight = 100.0f;
    bIsOpening = false;
}

void AMyDoor::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();
    TargetYaw = GetActorRotation().Yaw + OpenAngle;
}

void AMyDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsOpening)
    {
        // Calculate new yaw rotation
        float NewYaw = FMath::FInterpTo(GetActorRotation().Yaw, TargetYaw, DeltaTime, OpeningSpeed);

        // Set new rotation
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw = NewYaw;
        SetActorRotation(NewRotation);

        // Check if door is fully opened
        if (FMath::IsNearlyEqual(NewYaw, TargetYaw, 1.0f))
        {
            bIsOpening = false;
        }
    }
}

void AMyDoor::OpenDoor()
{
    if (!bIsOpening)
    {
        TargetYaw = GetActorRotation().Yaw + OpenAngle;
        bIsOpening = true;
    }
}


