// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Components/AudioComponent.h"
#include "MyPlayerController.h"

#include "Sound/SoundCue.h" 
#include "ChallengeAcepted3Character.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);
class AMyWeapon;

UCLASS(config = Game)
class AChallengeAcepted3Character : public ACharacter
{
	GENERATED_BODY()

public:
	void StartFiring();
	void StopFiring();
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float TurnRateGamepad;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		AMyWeapon* EquippedWeapon;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
		FOnUseItem OnUseItem;
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(AMyWeapon* NewWeapon);
public:
	AChallengeAcepted3Character();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:
	void OnPrimaryAction();
	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() : bIsPressed(false), Location(FVector::ZeroVector), bMoved(false) {}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};

	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);

	TouchData TouchItem;

	bool EnableTouchscreenMovement(UInputComponent* InputComponent);
};





