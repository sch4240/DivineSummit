// Fill out your copyright notice in the Description page of Project Settings.


#include "DTrainingMode.h"
#include "DivineSummit/Components/DHealthComponent.h"
#include "Kismet/GameplayStatics.h"
void ADTrainingMode::RestartDeadPlayers()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() == nullptr)
		{
			RestartPlayer(PC);
		}
	}
}

void ADTrainingMode::GameOver()
{
	UE_LOG(LogTemp, Log, TEXT("GAME OVER! Players Died"));
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	//RestartDeadPlayers();
}

ADTrainingMode::ADTrainingMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
}

void ADTrainingMode::CheckAnyPlayerAlive()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn())
		{
			APawn* MyPawn = PC->GetPawn();
			UDHealthComponent* HealthComp = Cast<UDHealthComponent>(MyPawn->GetComponentByClass(UDHealthComponent::StaticClass()));
			if (ensure(HealthComp) && HealthComp->GetHealth() > 0.0f)
			{
				// A player is still alive.
				return;
			}
		}
	}
	GameOver();
}

void ADTrainingMode::StartPlay()
{
	Super::StartPlay();
}

void ADTrainingMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CheckAnyPlayerAlive();
}
