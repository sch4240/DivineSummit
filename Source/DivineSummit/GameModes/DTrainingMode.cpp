// Fill out your copyright notice in the Description page of Project Settings.


#include "DTrainingMode.h"
#include "DivineSummit/Components/DHealthComponent.h"
#include "Kismet/GameplayStatics.h"


void ADTrainingMode::GameOver()
{

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

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* TestPawn = It->Get();

		if (TestPawn == nullptr || TestPawn->IsPlayerControlled())
		{
			continue;
		}

		UDHealthComponent* HealthComp = Cast<UDHealthComponent>(TestPawn->GetComponentByClass(UDHealthComponent::StaticClass()));
		if (HealthComp && HealthComp->GetHealth() == 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("GAME OVER! %s Died"), *(HealthComp->GetOwner()->GetName()));
			GameOver();
		}
	}

		
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














//void ADTrainingMode::RestartDeadPlayers()
//{
//	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
//	{
//		AController* PC = It->Get();
//		if (PC && PC->GetPawn() == nullptr)
//		{
//			RestartPlayer(PC);
//		}
//	}
//}
