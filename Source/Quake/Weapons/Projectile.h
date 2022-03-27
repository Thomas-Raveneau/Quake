// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Characters/QuakePlayer.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

#define PURE_VIRTUAL_VOID(func) { LowLevelFatalError(TEXT("Pure virtual not implemented (%s)"), TEXT(#func)); }
#define PURE_VIRTUAL_NUM(func) { LowLevelFatalError(TEXT("Pure virtual not implemented (%s)"), TEXT(#func)); return -1;}

UCLASS()
class QUAKE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void ApplyDamage(AQuakePlayer* Player);

	UFUNCTION(BlueprintCallable, Category = "Effects")
		virtual int GetDamage() PURE_VIRTUAL_NUM(AProjectile::GetDamage);
};
