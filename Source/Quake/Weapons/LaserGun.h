// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "LaserGun.generated.h"

#define FIRE_RATE 0.5f


/**
 * 
 */
UCLASS()
class QUAKE_API ALaserGun : public AWeapon
{
	GENERATED_BODY()

private:
	UPROPERTY()
		float FireRate = FIRE_RATE;

public:
	// Returns fire rate value
	virtual float GetFireRate() override;
	
};
