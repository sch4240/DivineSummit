// Fill out your copyright notice in the Description page of Project Settings.


#include "DGodAIController.h"
#include "Kismet/GameplayStatics.h"
#include "DivineSummit/Characters/DHeroCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DivineSummit/Characters/DGodCharacter.h"
#include "DivineSummit/Actors/DPlant.h"
void ADGodAIController::BeginPlay()
{
	Super::BeginPlay();


    if (PlayerPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found Player"));
        SetFocus(PlayerPawn);
    }

	GetWorldTimerManager().SetTimer(TimerHandle_MoveTimer, this, &ADGodAIController::MoveGod, MovementRate, true);
    GetWorldTimerManager().SetTimer(TimerHandle_PlantTimer, this, &ADGodAIController::SpawnPlantAtLocation, PlantSpawnRate, true);

}


void ADGodAIController::MoveToPlayer(int acceptance_radius)
{
    if (PlayerPawn)
    MoveToActor(PlayerPawn, acceptance_radius);
}


void ADGodAIController::MoveGod()
{
    if ((rand() % 100) % 4 == 0)
    {
        int x = UKismetMathLibrary::RandomIntegerInRange(0, n_rows - 1);
        int y = UKismetMathLibrary::RandomIntegerInRange(0, n_cols - 1);
        MoveToPoint(x, y);
        UE_LOG(LogTemp, Warning, TEXT("God: Moving To Point"));
    }
		
    else
    {
        MoveToPlayer(20);
        UE_LOG(LogTemp, Warning, TEXT("Moving To HERO"));
    }
     
}


bool ADGodAIController::PlayerInRange()
{

    if (PlayerPawn)
    {

        auto const& playerLoc = PlayerPawn->GetActorLocation();
        float distance = UKismetMathLibrary::Vector_Distance(GodPawn->GetActorLocation(), playerLoc);

        return distance < PlayerDetectBound;
    }
    return false;

}
void ADGodAIController::SpawnPlantAtLocation()
{

    if (PlayerInRange())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Detected Player"));
        // Set Timer to respawn powerup
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        if (PlayerPawn)
            PlantInstance = GetWorld()->SpawnActor<ADPlant>(PlantClass, PlayerPawn->GetTransform(), SpawnParams);
        // put delay
    }

}