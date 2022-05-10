// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "LaserProjectiles.generated.h"

#define LASER_DAMAGE 8

UCLASS()
class QUAKE_API ALaserProjectiles : public AProjectile
{
	GENERATED_BODY()
		
public:
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		int LaserDamage = LASER_DAMAGE;
public:
	virtual int GetDamage() override;
};
