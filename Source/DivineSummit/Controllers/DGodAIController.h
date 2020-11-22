// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DGodAIController.generated.h"

/**
 * 
 */

class ADHeroCharacter;

UCLASS()
class DIVINESUMMIT_API ADGodAIController : public AAIController
{
	GENERATED_BODY()
	

private:

	ADHeroCharacter* PlayerPawn;

	FTimerHandle TimerHandle_MoveTimer;


	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementRate = 3;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveGod();
};
