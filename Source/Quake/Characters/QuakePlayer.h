// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Weapons/Weapon.h"

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "QuakePlayer.generated.h"

UCLASS()
class QUAKE_API AQuakePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuakePlayer();

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called to configure class members replication
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	// Player health properties
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats")
		int Health = 100;
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		int MaxHealth = 200;

	// Player shield properties
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats")
		int Shield = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		int MaxShield = 200;

	// Player first and third person weapons
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Weapon")
		AWeapon* WeaponFP;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Weapon")
		AWeapon* WeaponTP;

public:
	// Health management
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Stats")
		void ServerAddHealth(int amount);
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Stats")
		void MulticastAddHealth(int amount);
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Stats")
		void ServerSubstractHealth(int amount);
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Stats")
		void MulticastSubstractHealth(int amount);

	// Shield management
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void AddShield(int amount);
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SubstractShield(int amount);

private:
	// Inputs management
	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);
	UFUNCTION()
		void Turn(float Value);
	UFUNCTION()
		void LookUp(float Value);

	UFUNCTION()
		void HandleDeath();
};