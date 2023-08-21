#include "MyWeapon.h"

// Aquí es donde inicializamos el miembro estático SoundFinder.

AMyWeapon::AMyWeapon()
{
    PrimaryActorTick.bCanEverTick = true;
   
    GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
    RootComponent = GunMesh;
    GunMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
    if (MeshFinder.Succeeded())
    {
        GunMesh->SetSkeletalMesh(MeshFinder.Object);
    }

    // Cambiamos el nombre de la variable local SoundFinder a LocalSoundFinder
    static ConstructorHelpers::FObjectFinder<USoundBase> LocalSoundFinder(TEXT("SoundWave'/Game/FPWeapon/Audio/FirstPersonTemplateWeaponFire02.FirstPersonTemplateWeaponFire02'"));
    if (LocalSoundFinder.Succeeded())
    {
        FireSound = LocalSoundFinder.Object;
    }
    BalloonClass = ABalloon::StaticClass();
    // Eliminamos la caja de recogida y toda la lógica asociada
    bIsPickedUp = true;
}

void AMyWeapon::BeginPlay()
{
    Super::BeginPlay();
    // Your BeginPlay logic here
}

void AMyWeapon::StartFiring()
{
    bIsFiring = true;
    Fire(); // Implementa tu lógica de disparo aquí
}

void AMyWeapon::StopFiring()
{
    bIsFiring = false;
    // Implementa lógica para detener el disparo si es necesario
}

void AMyWeapon::Fire()
{
    if (FireSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());    
    }

    // Crea un globo y "dispara" hacia adelante
    FVector SpawnLocation = GunMesh->GetSocketLocation("Muzzle");  // Asumiendo que tienes un socket llamado "Muzzle" en tu arma donde quieres que aparezcan los globos.
    FRotator SpawnRotation = GunMesh->GetSocketRotation("Muzzle");

    ABalloon* NewBalloon = GetWorld()->SpawnActor<ABalloon>(BalloonClass, SpawnLocation, SpawnRotation);
    if (NewBalloon)
    {
        NewBalloon->OnShot();
        // Añade velocidad al globo para que "dispare" hacia adelante
        FVector ShootingDirection = SpawnRotation.Vector();

        NewBalloon->BalloonMesh->AddImpulse(ShootingDirection * ShootingForce); // ShootingForce puede ser un valor constante o una variable en MyWeapon.
    }
    if (GreenBalloonsShot >= GreenBalloonsThreshold )
    {
        UE_LOG(LogTemp, Error, TEXT("Puerta Abierta"));
        DoorToOpen->OpenDoor();
    }
}

void AMyWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Tu lógica para Tick aquí
}










