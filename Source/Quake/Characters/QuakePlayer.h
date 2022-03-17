// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <algorithm>

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;

public:
	// Player health properties
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats")
	int Health = 100;
	const int MaxHealth = 200;

	// Player shield properties
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Stats")
	int Shield = 0;
	const int MaxShield = 200;
	
	// Player first and third person weapons
	UPROPERTY(Replicated, BlueprintReadWrite, Category="Weapon")
	AWeapon *WeaponFP;
	UPROPERTY(Replicated, BlueprintReadWrite, Category="Weapon")
	AWeapon *WeaponTP;

private:
	// Health management functions
	UFUNCTION(BlueprintCallable, Category="Stats")
	void AddHealth(int amount);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SubstractHealth(int amount);

	// Shield management functions
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddShield(int amount);
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SubstractShield(int amount);

	// Inputs function
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
	void Turn(float Value);
	UFUNCTION()
	void LookUp(float Value);
};
