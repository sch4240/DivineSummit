// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DivineSummit/Controllers/DBaseAIController.h"
#include <vector>
#include "DGodAIController.generated.h"

/**
 * 
 */

class ADHeroCharacter;
class ADPlant;

UCLASS()
class DIVINESUMMIT_API ADGodAIController : public ADBaseAIController
{
	GENERATED_BODY()
	

private:



	bool PlayerInRange();

	FTimerHandle TimerHandle_PlantTimer;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ADPlant> PlantClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float PlantSpawnRate = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float PlayerDetectBound = 1000;



	ADPlant* PlantInstance;


public:
	void MoveGod();

	void MoveToPlayer(int acceptance_radius);

	void SpawnPlantAtLocation();

};
