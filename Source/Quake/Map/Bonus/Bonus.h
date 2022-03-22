// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

#define PURE_VIRTUAL(func) { LowLevelFatalError(TEXT("Pure virtual not implemented (%s)"), TEXT(#func));}

UCLASS()
class QUAKE_API ABonus : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* BonusMesh;

	UPROPERTY(BlueprintReadWrite)
		bool Active = true;

private:
	// Respawn timer handler
	UPROPERTY()
	FTimerHandle TimerHandle;

public:	
	// Default ABonus constructor
	ABonus();
	// Default ABonus destructor
	virtual ~ABonus() {};

public:	
	// Called in derived class to apply bonus to the player
	UFUNCTION(BlueprintCallable)
	virtual void ApplyBonus() PURE_VIRTUAL(ABonus::ApplyBonus);

	// Called when the player activate the bonus
	UFUNCTION(BlueprintCallable)
		void Activate();

	// Called when the bonus needs to respawn after the respawn time is out
	UFUNCTION()
		void Respawn();

	// Returns RespawnTime value
	UFUNCTION(BlueprintCallable)
		virtual float GetRespawnTime();
};
