// Fill out your copyright notice in the Description page of Project Settings.


#include "DGodAIController.h"
#include "Kismet/GameplayStatics.h"
#include "DivineSummit/Characters/DHeroCharacter.h"
void ADGodAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<ADHeroCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	GetWorldTimerManager().SetTimer(TimerHandle_MoveTimer, this, &ADGodAIController::MoveGod, MovementRate, true);
	SetFocus(PlayerPawn);

}

void ADGodAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}



void ADGodAIController::MoveGod()
{
	if ((rand() % 100) % 5 == 0)
		MoveToLocation(FVector{ 890, 960, 198 });
	else
		MoveToActor(PlayerPawn, 20);
}