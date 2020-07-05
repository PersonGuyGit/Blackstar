// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlackstarHealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UBlackstarHealthComponent*, OwningHealthComp, float,
                                   Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*,
                                   InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLACKSTAR_API UBlackstarHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlackstarHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bIsDead();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float BaseHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float BaseArmor;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
public:	
	UFUNCTION()
	float GetHealth() const;

	UFUNCTION()
	float GetArmor() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health Comp")
	void HealCharacter(float HealTotal);

	UFUNCTION(BlueprintCallable, Category = "Health Comp")
	void RepairArmor(float ArmorTotal);

	
};
