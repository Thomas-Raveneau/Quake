// Fill out your copyright notice in the Description page of Project Settings.

#include "QuakePlayer.h"

// Sets default values
AQuakePlayer::AQuakePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicates(true);
}

// Called to bind functionality to input
void AQuakePlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AQuakePlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AQuakePlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AQuakePlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AQuakePlayer::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AQuakePlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AQuakePlayer::StopJumping);

	PlayerInputComponent->BindAction(TEXT("RespawnDebug"), IE_Pressed, this, &AQuakePlayer::HandleDeath);
}

// Called to configure class members replication
void AQuakePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AQuakePlayer, WeaponFP);
	DOREPLIFETIME(AQuakePlayer, WeaponTP);
	DOREPLIFETIME(AQuakePlayer, Health);
	DOREPLIFETIME(AQuakePlayer, Shield);
}

// Health management
void AQuakePlayer::ServerAddHealth_Implementation(int amount)
{
	Health = Health + amount > MaxHealth ? MaxHealth : Health + amount;
	//MulticastAddHealth(Health);
}

void AQuakePlayer::MulticastAddHealth_Implementation(int amount)
{
	Health = Health + amount > MaxHealth ? MaxHealth : Health + amount;
}

void AQuakePlayer::ServerSubstractHealth_Implementation(int amount)
{
	Health = Health - amount < 0 ? 0 : Health - amount;

	if (Health == 0) {
		HandleDeath();
	}

	//MulticastSubstractHealth(amount);
}

void AQuakePlayer::MulticastSubstractHealth_Implementation(int amount)
{
	Health = Health - amount < 0 ? 0 : Health - amount;
}

// Shield management
void AQuakePlayer::AddShield(int amount)
{
	Shield = Shield + amount > MaxShield ? MaxShield : Shield + amount;
}

void AQuakePlayer::SubstractShield(int amount)
{
	Shield = Shield - amount < 0 ? 0 : Shield - amount;
}

// Inputs management
void AQuakePlayer::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AQuakePlayer::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AQuakePlayer::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AQuakePlayer::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AQuakePlayer::HandleDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("DIE")));
}