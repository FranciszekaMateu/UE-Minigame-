#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "TP_PickUpComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AActor*, Actor);


// Pre-declara AChallengeAcepted3Character
class AChallengeAcepted3Character;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CHALLENGEACEPTED3_API UTP_PickUpComponent : public USphereComponent
{
    GENERATED_BODY()

public:
    UTP_PickUpComponent();

    virtual void BeginPlay() override;

    UPROPERTY(BlueprintAssignable)
        FOnPickUp OnPickUp;

protected:
    UFUNCTION()
        void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    float SphereRadius;
};
