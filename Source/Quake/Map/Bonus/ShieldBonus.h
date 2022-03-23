// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "ShieldBonus.generated.h"

/**
 * 
 */
UCLASS()
class QUAKE_API AShieldBonus : public ABonus
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
		int ShieldAmount = 50;
	UPROPERTY(BlueprintReadOnly)
		float RespawnTime = 20.0f;

public:
	// Add shield to the player
	virtual void ApplyBonus() override;

	// Returns RespawnTime value
	virtual float GetRespawnTime() override;

};
