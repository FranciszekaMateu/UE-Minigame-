#include "TP_WeaponComponent.h"
#include "ChallengeAcepted3Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

UTP_WeaponComponent::UTP_WeaponComponent()
	: MuzzleOffset(100.0f, 0.0f, 10.0f) // Utilizar lista de inicialización.
{}

void UTP_WeaponComponent::Fire()
{
	if (!Character || !Character->GetController())
		return;

	if (ProjectileClass)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			if (PlayerController) // Asegúrate de que el casting fue exitoso.
			{
				const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
				const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				World->SpawnActor<AChallengeAcepted3Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	if (FireSound)
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());

	if (FireAnimation)
	{
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance)
			AnimInstance->Montage_Play(FireAnimation, 1.f);
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character)
		Character->OnUseItem.RemoveDynamic(this, &UTP_WeaponComponent::Fire);
}

void UTP_WeaponComponent::AttachWeapon(AChallengeAcepted3Character* TargetCharacter)
{
	Character = TargetCharacter;

	if (Character)
	{
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		GetOwner()->AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
		Character->OnUseItem.AddDynamic(this, &UTP_WeaponComponent::Fire);
	}
}



