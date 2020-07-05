// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerupActor.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

class USphereComponent;
class UDecalComponent;
class APowerupActor;

UCLASS()
class BLACKSTAR_API APickupActor : public AActor
{
    GENERATED_BODY()
	
	public:	
        // Sets default values for this actor's properties
        APickupActor();

	protected:
        // Called when the game starts or when spawned
        virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
    UDecalComponent* DecalComp;

	UPROPERTY(EditInstanceOnly, Category = "PickupActor")
    TSubclassOf<APowerupActor> PowerUpClass;

	APowerupActor* PowerUpInstance;

	UPROPERTY(EditInstanceOnly, Category = "PickupActor")
    float CooldownDuration;

	FTimerHandle TimerHandle_RespawnTimer;

	void Respawn();

	public:	

        virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
};