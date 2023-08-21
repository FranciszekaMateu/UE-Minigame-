// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChallengeAcepted3Character.h"
#include "ChallengeAcepted3Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "MyPlayerController.h"
#include "GameFramework/InputSettings.h"
#include "MyWeapon.h"
//////////////////////////////////////////////////////////////////////////
// AChallengeAccepted3Character3

AChallengeAcepted3Character::AChallengeAcepted3Character()
{
    USoundBase* MusicCue = LoadObject<USoundBase>(nullptr, TEXT("/Game/StarterContent/Audio/Starter_Music_Cue.Starter_Music_Cue"));

    if (MusicCue)
    {
        // Reproducir la música
        UGameplayStatics::PlaySound2D(this, MusicCue);
    }
    // Set size for collision capsule
    if (GetCapsuleComponent())
    {
        GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Capsule component is null"));
    }
    EquippedWeapon = nullptr;
    // Set turn rates for input
    TurnRateGamepad = 45.f;

    // Create a CameraComponent    
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    if (FirstPersonCameraComponent)
    {
        FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
        FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
        FirstPersonCameraComponent->bUsePawnControlRotation = true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Camera component creation failed"));
    }

    // Create a mesh component for first person view
    Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
    if (Mesh1P)
    {
        Mesh1P->SetOnlyOwnerSee(true);
        Mesh1P->SetupAttachment(FirstPersonCameraComponent);
        Mesh1P->bCastDynamicShadow = false;
        Mesh1P->CastShadow = false;
        Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
        Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Mesh component creation failed"));
    }

}

void AChallengeAcepted3Character::BeginPlay()
{
    AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(GetController());
    if (MyPlayerController)
    {
        MyPlayerController->ShowIntroMessage();
    }
    Super::BeginPlay();
    if (!EquippedWeapon)
    {
        EquippedWeapon = GetWorld()->SpawnActor<AMyWeapon>();
        if (EquippedWeapon)
        {
            EquipWeapon(EquippedWeapon);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn weapon"));
        }
    }
}

void AChallengeAcepted3Character::OnPrimaryAction()
{
    // Trigger the OnItemUsed Event
    OnUseItem.Broadcast();
}

void AChallengeAcepted3Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    if (TouchItem.bIsPressed == true)
    {
        return;
    }
    if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
    {
        OnPrimaryAction();
    }
    TouchItem.bIsPressed = true;
    TouchItem.FingerIndex = FingerIndex;
    TouchItem.Location = Location;
    TouchItem.bMoved = false;
}

void AChallengeAcepted3Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    if (TouchItem.bIsPressed == false)
    {
        return;
    }
    TouchItem.bIsPressed = false;
}

void AChallengeAcepted3Character::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AChallengeAcepted3Character::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void AChallengeAcepted3Character::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AChallengeAcepted3Character::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool AChallengeAcepted3Character::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
    if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
    {
        PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AChallengeAcepted3Character::BeginTouch);
        PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AChallengeAcepted3Character::EndTouch);
        return true;
    }
    return false;
}

void AChallengeAcepted3Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    if (PlayerInputComponent)
    {
        // Bind jump events
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
        PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

        // Bind fire event
        PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AChallengeAcepted3Character::OnPrimaryAction);

        // Enable touchscreen input
        EnableTouchscreenMovement(PlayerInputComponent);

        // Bind movement events
        PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AChallengeAcepted3Character::MoveForward);
        PlayerInputComponent->BindAxis("Move Right / Left", this, &AChallengeAcepted3Character::MoveRight);

        // Rotation bindings
        PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
        PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
        PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AChallengeAcepted3Character::TurnAtRate);
        PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AChallengeAcepted3Character::LookUpAtRate);
        PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AChallengeAcepted3Character::StartFiring);
        PlayerInputComponent->BindAction("PrimaryAction", IE_Released, this, &AChallengeAcepted3Character::StopFiring);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerInputComponent is null"));
    }
}

void AChallengeAcepted3Character::EquipWeapon(AMyWeapon* NewWeapon)
{
    if (NewWeapon)
    {
        EquippedWeapon = NewWeapon;
        NewWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("GripPoint"));
        NewWeapon->SetActorHiddenInGame(false);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Attempted to equip null weapon"));
    }
}
void AChallengeAcepted3Character::StartFiring()
{
    if (EquippedWeapon)
    {
        EquippedWeapon->StartFiring();
    }
}

void AChallengeAcepted3Character::StopFiring()
{
    if (EquippedWeapon)
    {
        EquippedWeapon->StopFiring();
    }
}


