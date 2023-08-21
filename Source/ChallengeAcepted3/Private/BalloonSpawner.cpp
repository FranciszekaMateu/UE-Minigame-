#include "BalloonSpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/ConstructorHelpers.h"

ABalloonSpawner::ABalloonSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    MinSpawnInterval = 1.0f;
    MaxSpawnInterval = 5.0f;

    SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
    RootComponent = SpawnVolume;

    static ConstructorHelpers::FClassFinder<ABalloon> BalloonBP(TEXT("/Game/Blueprints/BP_Balloon"));
    if (BalloonBP.Succeeded())
    {
        BalloonBlueprint = BalloonBP.Class;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No se encontró el BP_BALLON"));
    }
}

void ABalloonSpawner::BeginPlay()
{
    Super::BeginPlay();
    ScheduleNextSpawn();
}

void ABalloonSpawner::ScheduleNextSpawn()
{
    float SpawnDelay = FMath::RandRange(MinSpawnInterval, MaxSpawnInterval);
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ABalloonSpawner::SpawnBalloon, SpawnDelay, false);
}

void ABalloonSpawner::SpawnBalloon()
{
    UWorld* World = GetWorld();
    if (World && BalloonBlueprint)
    {
        FVector SpawnOrigin = SpawnVolume->Bounds.Origin;
        FVector SpawnExtent = SpawnVolume->Bounds.BoxExtent;
        FVector SpawnLocation = FMath::RandPointInBox(FBox(SpawnOrigin - SpawnExtent, SpawnOrigin + SpawnExtent));

        FRotator SpawnRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

        World->SpawnActor<ABalloon>(BalloonBlueprint, SpawnLocation, SpawnRotation);

        ScheduleNextSpawn();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Mundo o Blueprint no disponible para spawnear."));
    }
}









