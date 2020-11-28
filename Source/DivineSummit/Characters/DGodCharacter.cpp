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
#include "DivineSummit/GameModes/DTrainingMode.h"


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

	//if (player)
	//	UE_LOG(LogTemp, Warning, TEXT("Player Found"));
}

void ADGodCharacter::OnHealthChanged(UDHealthComponent* OwningHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("God Health Dropped"));
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
void ADGodCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



