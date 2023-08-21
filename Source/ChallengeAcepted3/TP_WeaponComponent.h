#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChallengeAcepted3Character.h"
#include "TP_WeaponComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CHALLENGEACEPTED3_API UTP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTP_WeaponComponent();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Fire();
	void AttachWeapon(AChallengeAcepted3Character* TargetCharacter);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		UClass* ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		UAnimMontage* FireAnimation;

	AChallengeAcepted3Character* Character;
};

