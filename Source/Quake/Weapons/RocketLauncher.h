// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "RocketLauncher.generated.h"


// Weapon stats
#define FIRE_RATE 0.8f

UCLASS()
class QUAKE_API ARocketLauncher : public AWeapon
{
	GENERATED_BODY()
	

private:
	UPROPERTY()
		float FireRate = FIRE_RATE;

public: 
	ARocketLauncher();

	// Returns fire rate value
	virtual float GetFireRate() override;
};
