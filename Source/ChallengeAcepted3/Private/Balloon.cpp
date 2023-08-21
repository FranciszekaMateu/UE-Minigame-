#include "Balloon.h"
#include "UObject/ConstructorHelpers.h"

#include "Balloon.h"
#include "UObject/ConstructorHelpers.h"

ABalloon::ABalloon()
{
    PrimaryActorTick.bCanEverTick = true;

    bIsGreen = true;
    ColorChangeInterval = 5.0f;
    Amplitude = 1.0f;
    Frequency = 1.0f;
    SinusoidalOffset = 0.0f;

    BalloonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BalloonMesh"));
    RootComponent = BalloonMesh;

    // Establecer el mesh como una esfera
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (MeshFinder.Succeeded())
    {
        BalloonMesh->SetStaticMesh(MeshFinder.Object);
    }

    // Buscar el material verde
    static ConstructorHelpers::FObjectFinder<UMaterial> GreenMaterialFinder(TEXT("Material'/Game/Materials/Green_Material.Green_Material'"));
    if (GreenMaterialFinder.Succeeded())
    {
        GreenMaterial = GreenMaterialFinder.Object;
    }

    // Buscar el material rojo
    static ConstructorHelpers::FObjectFinder<UMaterial> RedMaterialFinder(TEXT("Material'/Game/Materials/Red_Material.Red_Material'"));
    if (RedMaterialFinder.Succeeded())
    {
        RedMaterial = RedMaterialFinder.Object;
    }
}

void ABalloon::BeginPlay()
{
    Super::BeginPlay();

    // Inicialmente configurar el material verde
    SetMaterial(GreenMaterial);

    GetWorldTimerManager().SetTimer(ColorChangeTimerHandle, this, &ABalloon::ChangeColor, ColorChangeInterval, true);
    BalloonMesh->SetWorldScale3D(FVector(0.0f));

    GetWorldTimerManager().SetTimer(InflateTimerHandle, this, &ABalloon::Inflate, 0.05f, true);
}

void ABalloon::ChangeColor()
{
    bIsGreen = !bIsGreen;
    OnColorChanged();
}

void ABalloon::OnColorChanged()
{
    if (bIsGreen)
    {
        SetMaterial(GreenMaterial);
    }
    else
    {
        SetMaterial(RedMaterial); // Asegúrate de definir RedMaterial en algún lugar o reemplazar esto con otro material que tengas.
    }
}

void ABalloon::SetMaterial(UMaterialInterface* Material)
{
    if (BalloonMesh)
    {
        BalloonMesh->SetMaterial(0, Material);
    }
}

void ABalloon::Inflate()
{
    FVector CurrentScale = BalloonMesh->GetComponentScale();
    FVector NewScale = FMath::VInterpTo(CurrentScale, FVector(1.0f), GetWorld()->GetDeltaSeconds(), 4.0f);
    BalloonMesh->SetWorldScale3D(NewScale);

    if (CurrentScale.Equals(FVector(1.0f), 0.05f))
    {
        GetWorldTimerManager().ClearTimer(InflateTimerHandle);
    }
}
void ABalloon::OnShot()
{
    // Cambia el color del globo a verde
    bIsGreen = true;
    SetMaterial(GreenMaterial);

    // Detener el cambio de color del globo
    if (ColorChangeTimerHandle.IsValid())
    {
        GetWorldTimerManager().ClearTimer(ColorChangeTimerHandle);
    }
}
void ABalloon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    SinusoidalOffset += (DeltaTime * Frequency);
    float Oscillation = FMath::Sin(SinusoidalOffset) * Amplitude;

    FVector NewLocation = GetActorLocation();
    NewLocation.X += Oscillation; // Oscilación lateral
    SetActorLocation(NewLocation);
}











