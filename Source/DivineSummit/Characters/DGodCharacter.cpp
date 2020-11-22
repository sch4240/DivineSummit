// Fill out your copyright notice in the Description page of Project Settings.


#include "DGodCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DivineSummit/DivineSummit.h"
#include "DivineSummit/Actors/DPlant.h"
#include "DivineSummit/Components/DHealthComponent.h"
#include "DivineSummit/Characters/DHeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"


// Sets default values
ADGodCharacter::ADGodCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UDHealthComponent>(TEXT("HealthComp"));

}

// Called when the game starts or when spawned
void ADGodCharacter::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ADHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GetWorldTimerManager().SetTimer(TimerHandle_PlantTimer, this, &ADGodCharacter::SpawnPlantAtLocation, PlantSpawnRate, true);
	//if (player)
	//	UE_LOG(LogTemp, Warning, TEXT("Player Found"));
}

void ADGodCharacter::OnHealthChanged(UDHealthComponent* OwningHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
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

bool ADGodCharacter::PlayerInRange()
{

	if (player)
	{
		float distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), player->GetActorLocation());

		return distance < PlayerDetectBound;
	}
	return false;
}

// Called every frame
void ADGodCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void ADGodCharacter::SpawnPlantAtLocation()
{

	if (PlayerInRange())
	{
		UE_LOG(LogTemp, Warning, TEXT("Detected Player"));
		// Set Timer to respawn powerup
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if(player)
			PlantInstance = GetWorld()->SpawnActor<ADPlant>(PlantClass, player->GetTransform(), SpawnParams);
		// put delay
	}

}

