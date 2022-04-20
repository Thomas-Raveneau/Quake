// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/KismetMathLibrary.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


UCLASS()
class QUAKE_API AWeapon : public AActor
{
	GENERATED_BODY()

public:	
	// Default constructor
	AWeapon();

	// Makes the weapon shoot
	UFUNCTION(BlueprintCallable)
		UPARAM(DisplayName = "ProjectileSpawnTransform") FTransform Shoot(FVector CameraForwardVector, FRotator CameraRotation);

	// Calculates shooting trajectory
	UFUNCTION()
		FHitResult GetShootingTrajectory(FVector MuzzleLocation, FVector CameraForwardVector);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		FVector GetMuzzleLocation();
};
