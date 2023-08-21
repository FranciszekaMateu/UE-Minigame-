#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChallengeAcepted3Projectile.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class UMaterialInterface;

UCLASS(config = Game)
class AChallengeAcepted3Projectile : public AActor
{
	GENERATED_BODY()

		/** Balloon mesh component */
		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent* BalloonMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

	/** Materials for balloon colors */
	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
		UMaterialInterface* GreenMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
		UMaterialInterface* RedMaterial;

	bool bIsGreen;
	float ColorChangeInterval;
	float Amplitude;
	float Frequency;
	float SinusoidalOffset;

	FTimerHandle ColorChangeTimerHandle;
	FTimerHandle InflateTimerHandle;

public:
	AChallengeAcepted3Projectile();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns BalloonMesh subobject **/
	UStaticMeshComponent* GetBalloonMesh() const { return BalloonMesh; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

private:
	void ChangeColor();
	void OnColorChanged();
	void SetMaterial(UMaterialInterface* Material);
	void Inflate();
};

