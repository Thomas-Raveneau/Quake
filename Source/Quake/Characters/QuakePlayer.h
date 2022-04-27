// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Weapons/Weapon.h"

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "QuakePlayer.generated.h"

// Base stats
#define SPAWN_HEALTH 50
#define SPAWN_SHIELD 25
#define MAX_HEALTH 100
#define MAX_SHIELD 100

UENUM(BlueprintType)
enum class EWeapon : uint8 {
	T_RocketLauncher	UMETA(DisplayName="Rocket_Launcher"),
	T_LaserGun			UMETA(DisplayName = "Laser_Gun"),
};

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
		int Health = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		int MaxHealth = MAX_HEALTH;

	// Player shield properties
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats")
		int Shield = 0;
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
		int MaxShield = MAX_SHIELD;

	// Player first and third person weapons
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Weapon")
		AWeapon* WeaponFP;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Weapon")
		AWeapon* WeaponTP;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Weapon")
		AWeapon* SecondaryWeaponFP;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Weapon")
		AWeapon* SecondaryWeaponTP;


public:
	// Damage management
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerTakeDamage(int amount, AController *instigatedBy, AActor *DamageCauser);

	// Health management
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerAddHealth(int amount);
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerSubstractHealth(int amount);
	

	// Shield management
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerAddShield(int amount);
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerSubstractShield(int amount);

protected: 
	//Called when our Actor is destroyed during Gameplay.
	virtual void Destroyed();

	//Call Gamemode class to Restart Player Character.
	void CallRestartPlayer();

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
	UFUNCTION(Server, Reliable)
		void ServerHandleDeath();
};