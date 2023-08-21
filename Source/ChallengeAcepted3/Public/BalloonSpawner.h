#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Balloon.h"
#include "Components/BoxComponent.h"
#include "BalloonSpawner.generated.h"

UCLASS()
class CHALLENGEACEPTED3_API ABalloonSpawner : public AActor
{
    GENERATED_BODY()

public:
    ABalloonSpawner();
    virtual void BeginPlay() override;

protected:
    void ScheduleNextSpawn();
    void SpawnBalloon();

    UPROPERTY(EditAnywhere, Category = "Spawn")
        float MinSpawnInterval;

    UPROPERTY(EditAnywhere, Category = "Spawn")
        float MaxSpawnInterval;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UBoxComponent* SpawnVolume;

    UPROPERTY(EditDefaultsOnly, Category = "Spawn")
        TSubclassOf<ABalloon> BalloonBlueprint;

private:
    FTimerHandle SpawnTimerHandle;
};





