// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DTrainingMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor, AController*, KillerController);


struct GameState
{
	float gameReset;
	float GodHealth, GodX, GodZ, GodPitch, GodSpawnedPlant, SpawnX, SpawnZ, HeroInPlant;
	float HeroHealth, HeroX, HeroZ, HeroPitch, HeroShot, BulletHitGod;
};
/**
 * 
 */
UCLASS()
class DIVINESUMMIT_API ADTrainingMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void CheckAnyPlayerAlive();

	//void RestartDeadPlayers();

	void GameOver();




public:
	ADTrainingMode();

	virtual void StartPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnActorKilled OnActorKilled;

	
	// Health
	bool PlayerDead{ false };
	bool GodDead{ false };
};
