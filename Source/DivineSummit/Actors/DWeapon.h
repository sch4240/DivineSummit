// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DWeapon.generated.h"


class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;

// Contains information of a single hitscan weapon linetrace
//USTRUCT()
//struct FHitScanTrace
//{
//	GENERATED_BODY()
//
//public:
//
//	UPROPERTY()
//		TEnumAsByte<EPhysicalSurface> SurfaceType;
//
//	UPROPERTY()
//		FVector_NetQuantize TraceTo;
//};


UCLASS()
class DIVINESUMMIT_API ADWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADWeapon();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	void PlayFireEffects(FVector TraceEnd);

	void PlayImpactEffects(EPhysicalSurface SurfaceType, FVector ImpactPoint);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShake> FireCamShake;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage;



	//UFUNCTION(Server, Reliable, WithValidation)
	//void ServerFire();

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;

	/* RPM - Bullets per minute fired by weapon */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire;

	/* Bullet Spread in Degrees */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin = 0.0f))
	float BulletSpread;

	// Derived from RateOfFire
	float TimeBetweenShots;

	//UPROPERTY(ReplicatedUsing = OnRep_HitScanTrace)
	//FHitScanTrace HitScanTrace;

	//UFUNCTION()
	//void OnRep_HitScanTrace();

public:	

	void StartFire();

	void StopFire();

	void Fire();

};