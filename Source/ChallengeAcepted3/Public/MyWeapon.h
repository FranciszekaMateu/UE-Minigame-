#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "../ChallengeAcepted3Character.h"
#include "Components/BoxComponent.h"
#include "Balloon.h"
#include "MyDoor.h"
#include "MyWeapon.generated.h"

UCLASS()
class CHALLENGEACEPTED3_API AMyWeapon : public AActor
{
	GENERATED_BODY()

public:
	AMyWeapon();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Fire();
	void StartFiring();
	void StopFiring();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		class AMyDoor* DoorToOpen;
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
		UBoxComponent* PickupBox;
	UPROPERTY(EditDefaultsOnly, Category = "Balloon")
		TSubclassOf<ABalloon> BalloonClass;
	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
		float ShootingForce = 5.0f;
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundFinder; // Miembro estático
	bool bIsPickedUp;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* GunMesh;
	static const int32 GreenBalloonsThreshold = 5;
	int32 GreenBalloonsShot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
		USoundBase* FireSound;
	bool bIsFiring;
};





