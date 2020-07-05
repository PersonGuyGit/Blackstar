// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;


USTRUCT()
struct FHitScanTrace
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TEnumAsByte<EPhysicalSurface> SurfaceType;

	UPROPERTY()
	FVector_NetQuantize TraceTo;
	
};


UCLASS()
class BLACKSTAR_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayFireEffects(FVector TraceEnd);

	void PlayImpactEffects(EPhysicalSurface SurfaceType, FVector ImpactPoint);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Comp")
	float BaseDamage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Comp")
	int D20;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Health Comp")
    void OnMisfire();
	
	UFUNCTION()
	void RollMissFire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Health Comp")
    void AltFire();

	UFUNCTION()
	void DoubleBarrelEntered();

	UFUNCTION()
	void DoubleBarrelReleased();
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin=0.0f))
    float BulletSpread;

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

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Comp")
	float RateOfFire;	
	
	float TimeBetweenShots;

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;

	UPROPERTY(ReplicatedUsing=OnRep_HitScanTrace)
	FHitScanTrace HitScanTrace;

	UFUNCTION()
	void OnRep_HitScanTrace();
	
	//Max Clip Ammo refers to the max capacity of the weapon class being used.
	//Example: A DB Shotgun would have a MaxClipAmmo of 2.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Comp")
	int MaxClipAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Comp")
	int CurrentAmmo;

	//Max Ammo is the MAX AMMO that you can carry on your back; example 300 rounds.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Comp")
	int MaxAmmo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire();

	UFUNCTION()
	int GetMaxAmmo() const;

	UFUNCTION()
    int GetCurrentAmmo();

	UFUNCTION()
    int GetMaxClipAmmo();

	void StartFire();

	void StopFire();

	bool CanFireFullAuto;

};
