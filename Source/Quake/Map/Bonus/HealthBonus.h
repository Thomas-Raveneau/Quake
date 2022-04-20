// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "HealthBonus.generated.h"

// Heal bonus stats
#define NORMAL_HEAL 50
#define MEGA_HEAL 75
#define NORMAL_RESPAWN_TIME 15.0f
#define MEGA_RESPAWN_TIME 20.0f

UCLASS()
class QUAKE_API AHealthBonus : public ABonus
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		int HealAmount = NORMAL_HEAL;
	UPROPERTY(BlueprintReadOnly)
		int MegaHealAmount = MEGA_HEAL;
	UPROPERTY(BlueprintReadOnly)
		float RespawnTime = NORMAL_RESPAWN_TIME;
	UPROPERTY(BlueprintReadOnly)
		float MegaRespawnTime = MEGA_RESPAWN_TIME;

public:
	// Heal the player
	virtual void ApplyBonus(AQuakePlayer* Player) override;

	// Returns RespawnTime value
	virtual float GetRespawnTime() override;

	// Returns HealAmount value
	virtual int GetBonusAmount() override;
};
