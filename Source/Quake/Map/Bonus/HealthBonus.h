// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "HealthBonus.generated.h"

/**
 *
 */
UCLASS()
class QUAKE_API AHealthBonus : public ABonus
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		int HealAmount = 50;
	UPROPERTY(BlueprintReadOnly)
		int MegaHealAmount = 75;
	UPROPERTY(BlueprintReadOnly)
		float RespawnTime = 15.0f;

public:
	// Heal the player
	virtual void ApplyBonus(AQuakePlayer* player) override;

	// Returns RespawnTime value
	virtual float GetRespawnTime() override;

	// Returns HealAmount value
	virtual int GetBonusAmount() override;
};
