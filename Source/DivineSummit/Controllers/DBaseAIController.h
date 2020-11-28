// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DBaseAIController.generated.h"

/**
 * 
 */


class ADGodCharacter;
UCLASS()
class DIVINESUMMIT_API ADBaseAIController : public AAIController
{
	GENERATED_BODY()


protected:
	FTimerHandle TimerHandle_MoveTimer;


	ADGodCharacter* GodPawn;
	class ADHeroCharacter* PlayerPawn;


	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementRate = 3;


	// grid settings
	AVolume* navMesh;
	FVector center, extent, point, point1, point2, point3, point4;
	FVector Start, End;

	int n_rows = 20;
	int	n_cols = 20;

	int x_step, y_step;
	std::vector< std::vector<FVector>> grid{ n_rows, std::vector<FVector>(n_cols) };
	

	virtual void BeginPlay() override;
	void MoveToPoint(int x, int y);


};
