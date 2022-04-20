// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponPoint.h"
#include "RocketLauncherPoint.generated.h"

#define AMMO_AMOUNT 1
#define RESPAWN_TIME 15.0f

UCLASS()
class QUAKE_API ARocketLauncherPoint : public AWeaponPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		int AmmoAmount = AMMO_AMOUNT;
	UPROPERTY(BlueprintReadOnly)
		float RespawnTime = RESPAWN_TIME;

public:
	// Give ammo to the player
	virtual void GiveAmmo(AQuakePlayer* Player) override;

	// Returns RespawnTime value
	virtual float GetRespawnTime() override;

	// Returns AmmoAmount value
	virtual int GetAmmoAmount() override;
};
