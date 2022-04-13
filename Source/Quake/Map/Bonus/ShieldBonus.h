// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "ShieldBonus.generated.h"

// Shield bonus stats
#define NORMAL_SHIELD 50
#define MEGA_SHIELD 75
#define NORMAL_RESPAWN_TIME 15.0f
#define MEGA_RESPAWN_TIME 20.0f

UCLASS()
class QUAKE_API AShieldBonus : public ABonus
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
		int ShieldAmount = NORMAL_SHIELD;
	UPROPERTY(BlueprintReadOnly)
		int MegaShieldAmount = MEGA_SHIELD;
	UPROPERTY(BlueprintReadOnly)
		float RespawnTime = NORMAL_RESPAWN_TIME;
	UPROPERTY(BlueprintReadOnly)
		float MegaRespawnTime = MEGA_RESPAWN_TIME;

public:
	// Add shield to the player
	virtual void ApplyBonus(AQuakePlayer* Player) override;

	// Returns RespawnTime value
	virtual float GetRespawnTime() override;

	// Returns ShieldAmount value
	virtual int GetBonusAmount() override;

};
