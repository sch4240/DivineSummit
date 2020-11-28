// Fill out your copyright notice in the Description page of Project Settings.


#include "DHeroAIController.h"
#include "Kismet/GameplayStatics.h"
#include "DivineSummit/Characters/DGodCharacter.h"
#include "DivineSummit/Characters/DHeroCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ADHeroAIController::BeginPlay()
{
    Super::BeginPlay();


    GetWorldTimerManager().SetTimer(TimerHandle_MoveTimer, this, &ADHeroAIController::ControlHero, MovementRate, true);
    if (GodPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found God"));
        SetFocus(GodPawn);
    }
}

void ADHeroAIController::MoveToGod(int acceptance_radius)
{
    if (GodPawn)
        MoveToActor(GodPawn, acceptance_radius);
}

void ADHeroAIController::ControlHero()
{
    auto random_number = UKismetMathLibrary::RandomIntegerInRange(0, 100);
    if (random_number < 20)
    {
        MoveToGod(20);
        UE_LOG(LogTemp, Warning, TEXT("Moving To GOD"));
    }

     
    else if (random_number > 80)
    {
     
        int x = UKismetMathLibrary::RandomIntegerInRange(0, n_rows - 1);
        int y = UKismetMathLibrary::RandomIntegerInRange(0, n_cols - 1);
        MoveToPoint(x, y);
        UE_LOG(LogTemp, Warning, TEXT("Player: Moving To Point"));
    }
    else
    {
        PlayerPawn->Fire();
    }
}
