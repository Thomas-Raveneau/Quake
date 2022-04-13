// Fill out your copyright notice in the Description page of Project Settings.

#include "QuakePlayer.h"
#include "../Gamemodes/Deathmatch.h"

// Sets default values
AQuakePlayer::AQuakePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	ServerAddHealth(SPAWN_HEALTH);
}

// Called to bind functionality to input
void AQuakePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AQuakePlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AQuakePlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AQuakePlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AQuakePlayer::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AQuakePlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AQuakePlayer::StopJumping);

	PlayerInputComponent->BindAction(TEXT("RespawnDebug"), IE_Pressed, this, &AQuakePlayer::ServerHandleDeath);
}

// Called to configure class members replication
void AQuakePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AQuakePlayer, WeaponFP);
	DOREPLIFETIME(AQuakePlayer, WeaponTP);
	DOREPLIFETIME(AQuakePlayer, Health);
	DOREPLIFETIME(AQuakePlayer, Shield);
}

// Damage management
void AQuakePlayer::ServerTakeDamage_Implementation(int amount, AController* instigatedBy, AActor* DamageCauser)
{
	AController* controllerRef = GetController();
	int damageToShield;
	int damageToHealth;
	int damageNotTakenByShield = 0;

	// Divide damage by 2 in case of self damage
	if (controllerRef == instigatedBy)
	{
		amount /= 2;
	}

	damageToShield = (amount * 2) / 3;									// Shield takes 2/3 of received damages

	if (Shield < damageToShield) 
	{
		damageNotTakenByShield = damageToShield - Shield;
	}

	damageToHealth = amount - damageToShield + damageNotTakenByShield;	// Health takes 1/3 of received damages

	ServerSubstractShield(damageToShield);
	ServerSubstractHealth(damageToHealth);

	// Check if player is dead
	if (Health == 0) {
		ServerHandleDeath();
	}
}

// Health management
void AQuakePlayer::ServerAddHealth_Implementation(int amount)
{
	Health = Health + amount > MaxHealth ? MaxHealth : Health + amount;
}

void AQuakePlayer::ServerSubstractHealth_Implementation(int amount)
{
	Health = Health - amount < 0 ? 0 : Health - amount;
}

// Shield management
void AQuakePlayer::ServerAddShield_Implementation(int amount)
{
	Shield = Shield + amount > MaxShield ? MaxShield : Shield + amount;
}

void AQuakePlayer::ServerSubstractShield_Implementation(int amount)
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

// Death management
void AQuakePlayer::Destroyed()
{
	Super::Destroyed();

	if (IsValid(WeaponTP))
	{
		WeaponTP->Destroy();
	}
	if (IsValid(WeaponFP))
	{
		WeaponFP->Destroy();
	}

	// Example to bind to OnPlayerDied event in GameMode. 
	if (UWorld* World = GetWorld())
	{
		if (ADeathmatch* GameMode = Cast<ADeathmatch>(World->GetAuthGameMode()))
		{
			GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
}

void AQuakePlayer::ServerHandleDeath_Implementation()
{
	//Get a reference to the Pawn Controller.
	AController* ControllerRef = GetController();

	//Destroy the Player.   
	Destroy();

	//Get the World and GameMode in the world to invoke its restart player function.
	if (UWorld* World = GetWorld())
	{
		if (ADeathmatch* GameMode = Cast<ADeathmatch>(World->GetAuthGameMode()))
		{
			GameMode->RespawnPlayer(ControllerRef);
		}
	}
}