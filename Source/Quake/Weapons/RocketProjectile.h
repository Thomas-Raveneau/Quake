// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "RocketProjectile.generated.h"

#define ROCKET_DAMAGE 125

UCLASS()
class QUAKE_API ARocketProjectile : public AProjectile
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		int RocketDamage = ROCKET_DAMAGE;
public:
	virtual int GetDamage() override;
};
