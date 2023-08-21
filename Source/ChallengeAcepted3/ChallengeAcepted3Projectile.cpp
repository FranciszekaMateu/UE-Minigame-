#include "ChallengeAcepted3Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AChallengeAcepted3Projectile::AChallengeAcepted3Projectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize your variables here
    bIsGreen = true;
    ColorChangeInterval = 5.0f;
    Amplitude = 1.0f;
    Frequency = 1.0f;
    SinusoidalOffset = 0.0f;

    // Balloon mesh setup
    BalloonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BalloonMesh"));
    RootComponent = BalloonMesh;

    // Projectile properties
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = BalloonMesh;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    InitialLifeSpan = 3.0f;
}

void AChallengeAcepted3Projectile::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(ColorChangeTimerHandle, this, &AChallengeAcepted3Projectile::ChangeColor, ColorChangeInterval, true);
    BalloonMesh->SetWorldScale3D(FVector(0.0f));
    GetWorldTimerManager().SetTimer(InflateTimerHandle, this, &AChallengeAcepted3Projectile::Inflate, 0.05f, true);
}

void AChallengeAcepted3Projectile::ChangeColor()
{
    bIsGreen = !bIsGreen;
    OnColorChanged();
}

void AChallengeAcepted3Projectile::OnColorChanged()
{
    if (bIsGreen)
    {
        SetMaterial(GreenMaterial);
    }
    else
    {
        SetMaterial(RedMaterial);
    }
}

void AChallengeAcepted3Projectile::SetMaterial(UMaterialInterface* Material)
{
    if (BalloonMesh)
    {
        BalloonMesh->SetMaterial(0, Material);
    }
}

void AChallengeAcepted3Projectile::Inflate()
{
    FVector CurrentScale = BalloonMesh->GetComponentScale();
    FVector NewScale = FMath::VInterpTo(CurrentScale, FVector(1.0f), GetWorld()->GetDeltaSeconds(), 4.0f);
    BalloonMesh->SetWorldScale3D(NewScale);

    if (CurrentScale.Equals(FVector(1.0f), 0.05f))
    {
        GetWorldTimerManager().ClearTimer(InflateTimerHandle);
    }
}

void AChallengeAcepted3Projectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    SinusoidalOffset += (DeltaTime * Frequency);
    float Oscillation = FMath::Sin(SinusoidalOffset) * Amplitude;

    FVector NewLocation = GetActorLocation();
    NewLocation.X += Oscillation;
    SetActorLocation(NewLocation);
}

void AChallengeAcepted3Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, GetActorLocation());
        Destroy();
    }
}

