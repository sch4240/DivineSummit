// Fill out your copyright notice in the Description page of Project Settings.


#include "DHealthComponent.h"

// Sets default values for this component's properties
UDHealthComponent::UDHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	DefaultHealth = 100;
	bIsDead = false;

	// ...
}


// Called when the game starts
void UDHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UDHealthComponent::HandleTakeAnyDamage);
	}
	// Only hook if we are server
	//if (GetOwnerRole() == ROLE_Authority)
	//{

	//}

	Health = DefaultHealth;
	// ...
	
}


void UDHealthComponent::OnRep_Health(float OldHealth)
{
	float Damage = Health - OldHealth;

	OnHealthChanged.Broadcast(this, Health, Damage, nullptr, nullptr, nullptr);
}


void UDHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy,
	AActor* DamageCauser)
{

	if (Damage <= 0.0f || bIsDead)
	{
		return;
	}
	
	//if (DamageCauser != DamagedActor)// && IsFriendly(DamagedActor, DamageCauser))
	//{
	//	return;
	//}

	// Update health clamped
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Log, TEXT("%s: Health Changed: %s"), *(GetOwner()->GetName()), *FString::SanitizeFloat(Health));

	bIsDead = Health <= 0.0f;

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);


}

float UDHealthComponent::GetHealth() const
{
	return Health;
}
