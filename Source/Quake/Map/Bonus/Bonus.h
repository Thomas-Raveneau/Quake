// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Characters/QuakePlayer.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

#define PURE_VIRTUAL_VOID(func) { LowLevelFatalError(TEXT("Pure virtual not implemented (%s)"), TEXT(#func)); }
#define PURE_VIRTUAL_NUM(func) { LowLevelFatalError(TEXT("Pure virtual not implemented (%s)"), TEXT(#func)); return -1;}

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
	UPROPERTY(BlueprintReadWrite)
		bool Mega = false;

private:
	// Respawn timer handler
	UPROPERTY()
		FTimerHandle TimerHandle;

public:
	// Default ABonus constructor
	ABonus();

public:
	// Called when the player activate the bonus
	UFUNCTION(BlueprintCallable)
		void Activate(AQuakePlayer *player);

	// Called when the bonus needs to respawn after the respawn time is out
	UFUNCTION()
		void Respawn();

	// Called in derived class to apply bonus to the player
	UFUNCTION(BlueprintCallable)
		virtual void ApplyBonus(AQuakePlayer* player) PURE_VIRTUAL_VOID(ABonus::ApplyBonus);

	// Called in derived class to get RespawnTime value
	UFUNCTION(BlueprintCallable)
		virtual float GetRespawnTime() PURE_VIRTUAL_NUM(ABonus::SetBonusAmount);

	// Called in derived class to get BonusAmount value
	UFUNCTION(BlueprintCallable)
		virtual int GetBonusAmount() PURE_VIRTUAL_NUM(ABonus::GetBonusAmount);
};
