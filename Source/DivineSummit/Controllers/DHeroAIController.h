// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DivineSummit/Controllers/DBaseAIController.h"
#include "DHeroAIController.generated.h"

/**
 * 
 */


UCLASS()
class DIVINESUMMIT_API ADHeroAIController : public ADBaseAIController
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveToGod(int acceptance_radius);

	void ControlHero();
	
};
