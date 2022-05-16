// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/KismetMathLibrary.h"

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

#define PURE_VIRTUAL_NUM(func) { LowLevelFatalError(TEXT("Pure virtual not implemented (%s)"), TEXT(#func)); return -1;}

UCLASS()
class QUAKE_API AWeapon : public AActor
{
	GENERATED_BODY()


public:
	UPROPERTY(Replicated, BlueprintReadWrite)
		bool CanShoot;

private:
	UPROPERTY()
		FTimerHandle FireRateTimerHandle;

public:	
	// Default constructor
	AWeapon();

	// Called to configure class members replication
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	// Makes the weapon shoot
	UFUNCTION(BlueprintCallable)
		UPARAM(DisplayName = "ProjectileSpawnTransform") FTransform Shoot(FVector CameraForwardVector, FRotator CameraRotation);

	// Calculates shooting trajectory
	UFUNCTION()
		FHitResult GetShootingTrajectory(FVector MuzzleLocation, FVector CameraForwardVector);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		FVector GetMuzzleLocation();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetWeaponVisibility(bool FPSView);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void PlayFireSound();

	UFUNCTION(BlueprintCallable)
		virtual float GetFireRate() PURE_VIRTUAL_NUM(AWeapon::GetFireRate);

private:
	UFUNCTION()
		void HandleFireRateTimerEnd();
};
