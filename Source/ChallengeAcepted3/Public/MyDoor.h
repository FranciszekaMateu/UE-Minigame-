// MyDoor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDoor.generated.h"
UCLASS()
class CHALLENGEACEPTED3_API AMyDoor : public AActor
{
    GENERATED_BODY()

public:
    AMyDoor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Door")
        void OpenDoor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
        UStaticMeshComponent* DoorMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
        float OpeningSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
        float OpenHeight;

private:
    float OpenAngle;
    float TargetYaw;
    bool bIsOpening;
    FVector InitialLocation;
};


