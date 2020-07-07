// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackstarHealthComponent.h"

// Sets default values for this component's properties
UBlackstarHealthComponent::UBlackstarHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	Health = 100.0f;
	Health = BaseHealth;

	BaseArmor = 50.0f;
	Armor = BaseArmor;
}


// Called when the game starts
void UBlackstarHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if(MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UBlackstarHealthComponent::HandleTakeAnyDamage);
	}
	
}

void UBlackstarHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f)
	{
		return;
	}

	if (Armor <= BaseArmor && Health == BaseHealth)
	{
		Armor = FMath::Clamp(Armor - Damage, 0.0f, BaseArmor);
	} 
	if(Armor  <= 0.0f)
	{
		Health = FMath::Clamp(Health - Damage, 0.0f, BaseHealth);
	}

	UE_LOG(LogTemp, Log, TEXT("Health value %s"), *FString::SanitizeFloat(Health));
	UE_LOG(LogTemp, Log, TEXT("Armor value %s"), *FString::SanitizeFloat(Armor));
}

float UBlackstarHealthComponent::GetHealth() const
{
	return Health;
}

float UBlackstarHealthComponent::GetArmor() const
{
	return Armor;
}



void UBlackstarHealthComponent::HealCharacter(float HealTotal)
{
	if (HealTotal <= 0 || Health <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health + HealTotal, 0.0f, BaseHealth);
}

void UBlackstarHealthComponent::RepairArmor(float ArmorTotal)
{

	if (ArmorTotal <= 0 || Armor <= 0) 
	{
		return;
	}

	Armor = FMath::Clamp(Armor + ArmorTotal, 0.0f, BaseArmor);
}







