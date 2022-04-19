// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Characters/QuakePlayer.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponPoint.generated.h"

#define PURE_VIRTUAL_VOID(func) { LowLevelFatalError(TEXT("Pure virtual not implemented (%s)"), TEXT(#func)); }
#define PURE_VIRTUAL_NUM(func) { LowLevelFatalError(TEXT("Pure virtual not implemented (%s)"), TEXT(#func)); return -1;}

UCLASS()
class QUAKE_API AWeaponPoint : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(BlueprintReadWrite)
		bool Active = true;

private:
	// Respawn timer handler
	UPROPERTY()
		FTimerHandle TimerHandle;

public:
	// Default AWeaponPoint constructor
	AWeaponPoint();

public:
	// Called when the player activate the point
	UFUNCTION(BlueprintCallable)
		void Activate(AQuakePlayer* Player);

	// Called when the bonus needs to respawn after the respawn time is out
	UFUNCTION()
		void Respawn();

	// Called in derived class to give ammos to the player
	UFUNCTION(BlueprintCallable)
		virtual void GiveAmmo(AQuakePlayer* Player) PURE_VIRTUAL_VOID(ABonus::GiveAmmo);

	// Called in derived class to get RespawnTime value
	UFUNCTION(BlueprintCallable)
		virtual float GetRespawnTime() PURE_VIRTUAL_NUM(ABonus::GetRespawnTime);

	// Called in derived class to get GetAmmoAmount value
	UFUNCTION(BlueprintCallable)
		virtual int GetAmmoAmount() PURE_VIRTUAL_NUM(ABonus::GetAmmoAmount);
};
