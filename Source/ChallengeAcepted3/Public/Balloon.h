#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"
#include "Balloon.generated.h"

UCLASS()
class CHALLENGEACEPTED3_API ABalloon : public AActor
{
    GENERATED_BODY()

public:
    // Constructor por defecto
    ABalloon();

    // Funciones de ciclo de vida de Actor
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    void OnShot();
    // Funciones para el comportamiento del globo
    UFUNCTION()
        void ChangeColor();

    UFUNCTION(BlueprintCallable, Category = "Balloon")
        void OnColorChanged();
    // Componentes y propiedades del globo
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Balloon")
        UStaticMeshComponent* BalloonMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balloon")
        bool bIsGreen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Balloon")
        float ColorChangeInterval;

    UPROPERTY(EditDefaultsOnly, Category = "Materials")
        UMaterialInterface* GreenMaterial;

    UPROPERTY(EditDefaultsOnly, Category = "Materials")
        UMaterialInterface* RedMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
        float Amplitude; // Esta es la amplitud de la oscilación lateral.

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
        float Frequency; // Esta es la frecuencia de la oscilación lateral.
    

private:
    // Funciones y propiedades privadas
    void SetMaterial(UMaterialInterface* Material);

    FTimerHandle InflateTimerHandle;
    void Inflate();

    FTimerHandle ColorChangeTimerHandle;

    float SinusoidalOffset; // Para controlar la oscilación lateral.
};










