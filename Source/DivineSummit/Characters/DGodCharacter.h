// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGodCharacter.generated.h"

class UDHealthComponent;
class ADHeroCharacter;
class ADPlant;

UCLASS()
class DIVINESUMMIT_API ADGodCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADGodCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDHealthComponent* HealthComp;

	ADHeroCharacter* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ADPlant> PlantClass;

	ADPlant* PlantInstance;


	UFUNCTION()
	void OnHealthChanged(UDHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/* Pawn died previously */
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bDied;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float PlantSpawnRate = 2;

	FTimerHandle TimerHandle_PlantTimer;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float PlayerDetectBound = 1000;

	bool PlayerInRange();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnPlantAtLocation();

};
