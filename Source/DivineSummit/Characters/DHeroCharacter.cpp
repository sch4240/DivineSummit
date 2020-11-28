// Fill out your copyright notice in the Description page of Project Settings.

#include "DHeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DivineSummit/DivineSummit.h"
#include "DivineSummit/Components/DHealthComponent.h"
#include "Net/UnrealNetwork.h"
#include "DivineSummit/GameModes/DTrainingMode.h"
#include "Kismet/GameplayStatics.h"
#include "DivineSummit/Actors/DWeapon.h"


// Sets default values
ADHeroCharacter::ADHeroCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	HealthComp = CreateDefaultSubobject<UDHealthComponent>(TEXT("HealthComp"));
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	WeaponAttachSocketName = "WeaponSocket";
	
}

// Called when the game starts or when spawned
void ADHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	HealthComp->OnHealthChanged.AddDynamic(this, &ADHeroCharacter::OnHealthChanged);

	// Spawn a default weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<ADWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}
}


void ADHeroCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}


void ADHeroCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}


void ADHeroCharacter::BeginCrouch()
{
	Crouch();
}


void ADHeroCharacter::EndCrouch()
{
	UnCrouch();
}



void ADHeroCharacter::OnHealthChanged(UDHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{

	UE_LOG(LogTemp, Warning, TEXT("Hero Health Dropped"));
	if (Health <= 0.0f && !bDied)
	{
		// Die!
		bDied = true;
		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DetachFromControllerPendingDestroy();

		SetLifeSpan(10.0f);
	}
}


// Called every frame
void ADHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("%s: Health Changed: %s"), *(GetName()), *FString::SanitizeFloat(HealthComp->GetHealth()));
}

// Called to bind functionality to input
void ADHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADHeroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADHeroCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ADHeroCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ADHeroCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADHeroCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ADHeroCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADHeroCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ADHeroCharacter::StopFire);

	// CHALLENGE CODE
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}


FVector ADHeroCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

void ADHeroCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}

}

void ADHeroCharacter::StopFire()
{
	if(CurrentWeapon)
		CurrentWeapon->StopFire();
}

void ADHeroCharacter::Fire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}


