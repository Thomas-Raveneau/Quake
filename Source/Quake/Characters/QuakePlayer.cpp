// Fill out your copyright notice in the Description page of Project Settings.

#include "QuakePlayer.h"

// Sets default values
AQuakePlayer::AQuakePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	InputsEnabled = true;

	ServerAddHealth(SPAWN_HEALTH);
	ServerAddShield(SPAWN_SHIELD);
	ServerAddRocket(SPAWN_ROCKET);
	ServerAddLaser(SPAWN_LASER);

}

// Called to bind functionality to input
void AQuakePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AQuakePlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AQuakePlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AQuakePlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AQuakePlayer::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AQuakePlayer::JumpStart);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AQuakePlayer::JumpStop);
}

// Called to configure class members replication
void AQuakePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AQuakePlayer, CurrentlyEquipped);
	DOREPLIFETIME(AQuakePlayer, WeaponFP);
	DOREPLIFETIME(AQuakePlayer, WeaponTP);
	DOREPLIFETIME(AQuakePlayer, Health);
	DOREPLIFETIME(AQuakePlayer, Shield);
	DOREPLIFETIME(AQuakePlayer, AmmoRocket);
	DOREPLIFETIME(AQuakePlayer, AmmoLaser);
	DOREPLIFETIME(AQuakePlayer, CurrentLaser);
	DOREPLIFETIME(AQuakePlayer, IsShootingLaser);
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

	// Shield takes 2/3 of received damages
	damageToShield = (amount * 2) / 3;

	if (Shield < damageToShield)
	{
		damageNotTakenByShield = damageToShield - Shield;
	}

	// Health takes 1/3 of received damages
	damageToHealth = amount - damageToShield + damageNotTakenByShield;

	// Apply damages to shield and health
	ServerSubstractShield(damageToShield);
	ServerSubstractHealth(damageToHealth);

	// Check if player is dead
	if (Health == 0) {
		ServerHandleDeath(instigatedBy);
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

// Ammos management
void AQuakePlayer::ServerAddLaser_Implementation(int amount)
{
	AmmoLaser = AmmoLaser + amount > MaxAmmoLaser ? MaxAmmoLaser : AmmoLaser + amount;
}

void AQuakePlayer::ServerSubstractLaser_Implementation(int amount)
{
	AmmoLaser = AmmoLaser - amount < 0 ? 0 : AmmoLaser - amount;
}


void AQuakePlayer::ServerAddRocket_Implementation(int amount)
{
	AmmoRocket = AmmoRocket + amount > MaxAmmoRocket ? MaxAmmoRocket : AmmoRocket + amount;
}

void AQuakePlayer::ServerSubstractRocket_Implementation(int amount)
{
	AmmoRocket = AmmoRocket - amount < 0 ? 0 : AmmoRocket - amount;
}

// Shooting management
void AQuakePlayer::Shoot(FVector CameraForwardVector, FRotator CameraRotation)
{
	switch (this->CurrentlyEquipped)
	{
		case(EWeapon::T_RocketLauncher):
		{
			if (AmmoRocket > 0 && WeaponFP->CanShoot)
			{
				FTransform rocketTransform = WeaponFP->Shoot(CameraForwardVector, CameraRotation);
				ServerSpawnProjectile(rocketTransform, this);
				ServerSubstractRocket(1);
			}
			break;
		}
		case(EWeapon::T_LaserGun):
		{
			if (AmmoLaser > 0 && WeaponFP->CanShoot)
			{
				FTransform laserTransform = WeaponFP->Shoot(CameraForwardVector, CameraRotation);
				ServerSpawnProjectile(laserTransform, this);
				ServerSubstractLaser(1);
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

// Spawn projectile of current weapon
void AQuakePlayer::ServerSpawnProjectile_Implementation(FTransform ProjectileTransform, AActor* ProjectileOwner)
{
	if (UWorld* World = GetWorld())
	{
		if (RocketActor && this->CurrentlyEquipped == EWeapon::T_RocketLauncher)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = ProjectileOwner;

			World->SpawnActor<AActor>(RocketActor, ProjectileTransform, spawnParams);
		}
		if (LaserActor && this->CurrentlyEquipped == EWeapon::T_LaserGun && !IsShootingLaser)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = ProjectileOwner;


			TArray<USkeletalMeshComponent*> SkeletalComps;

			WeaponFP->GetComponents<USkeletalMeshComponent>(SkeletalComps);

			for (int i = 0; i != SkeletalComps.Num(); i++)
			{
				if (SkeletalComps[i]->ComponentTags.Contains(TEXT("WeaponMesh")))
				{
					CurrentLaser = World->SpawnActor<AActor>(LaserActor, ProjectileTransform, spawnParams);
					CurrentLaser->AttachToComponent(SkeletalComps[i], FAttachmentTransformRules::SnapToTargetIncludingScale, "Muzzle_Bone");
					IsShootingLaser = true;
				}
			}
		}
	}
}

void AQuakePlayer::ServerDestroyLaser_Implementation()
{
	if (CurrentLaser)
	{
		CurrentLaser->Destroy();
		CurrentLaser = nullptr;
		IsShootingLaser = false;
	}
}

// Toggle IlayersInputs on client side
void AQuakePlayer::SetInputsEnabled(bool Enabled)
{
	InputsEnabled = Enabled;
}

// Inputs management
void AQuakePlayer::MoveForward(float Value)
{
	if (InputsEnabled)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AQuakePlayer::MoveRight(float Value)
{
	if (InputsEnabled)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AQuakePlayer::Turn(float Value)
{
	if (InputsEnabled)
	{
		AddControllerYawInput(Value);
	}
}

void AQuakePlayer::LookUp(float Value)
{
	if (InputsEnabled)
	{
		AddControllerPitchInput(Value);

	}
}

void AQuakePlayer::JumpStart()
{
	if (InputsEnabled)
	{
		Jump();
	}
}

void AQuakePlayer::JumpStop()
{
	if (InputsEnabled)
	{
		StopJumping();
	}
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

void AQuakePlayer::ServerHandleDeath_Implementation(AController* instigatedBy)
{
	//Get a reference to the Pawn Controller.
	AController* ControllerRef = GetController();


	//Destroy the Player.   
	Destroy();

	//Get the World and GameMode in the world to invoke its restart player function.
	if (UWorld* World = GetWorld())
	{
		if (ADeathmatchState* GameState = Cast<ADeathmatchState>(World->GetGameState()))
		{
			GameState->ServerHandleKill(instigatedBy, ControllerRef);
		}


		if (ADeathmatch* GameMode = Cast<ADeathmatch>(World->GetAuthGameMode()))
		{
			GameMode->RespawnPlayer(ControllerRef);
		}
	}
}