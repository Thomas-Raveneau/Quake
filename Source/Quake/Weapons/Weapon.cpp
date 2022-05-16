// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CanShoot = false;
	InstantShootWeapon = false;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	PlayWeaponSwapSound();
}

// Called to configure class members replication
void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, CanShoot);
	DOREPLIFETIME(AWeapon, InstantShootWeapon);
}

// Makes the weapon shoot
FTransform AWeapon::Shoot(FVector CameraForwardVector, FRotator CameraRotation)
{
	// TODO - Check weapon shooting conditions (ammo, etc...)
	const FVector MuzzleLocation = GetMuzzleLocation();
	const FHitResult ShootingTrajectory = GetShootingTrajectory(MuzzleLocation, CameraForwardVector);
	const FVector ProjectileSpawnLocation = MuzzleLocation;
	const FRotator ProjectileSpawnRotation = UKismetMathLibrary::GetDirectionUnitVector(MuzzleLocation, ShootingTrajectory.ImpactPoint).Rotation();
	const FTransform ProjectileSpawnTransform = FTransform(ProjectileSpawnRotation, ProjectileSpawnLocation);

	const float FireRate = GetFireRate();

	if (FireRate > 0)
	{
		CanShoot = false;
		PlayFireSound();
		GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AWeapon::HandleFireRateTimerEnd, FireRate, false, FireRate);
	}

	return ProjectileSpawnTransform;
}

FHitResult AWeapon::GetShootingTrajectory(FVector MuzzleLocation, FVector CameraForwardVector)
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	FVector Start;
	FVector End;
	FHitResult PlayerCamHit;
	FHitResult MuzzleHit;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	Start = PlayerLocation;
	End = Start + (CameraForwardVector * 20000);

	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(PlayerCamHit, Start, End, ECC_Visibility, TraceParams);

	FVector MuzzleStart = MuzzleLocation;
	FVector DirectVector = UKismetMathLibrary::GetDirectionUnitVector(MuzzleLocation, PlayerCamHit.ImpactPoint);
	FVector MuzzleEnd = PlayerCamHit.ImpactPoint + (DirectVector * 2);

	GetWorld()->LineTraceSingleByChannel(MuzzleHit, MuzzleStart, MuzzleEnd, ECC_Visibility, TraceParams);

	return 
		
		MuzzleHit;
}

void AWeapon::ServerSetInstantShootWeapon_Implementation(bool NewInstantShootWeapon)
{	
	InstantShootWeapon = NewInstantShootWeapon;
}

void AWeapon::HandleFireRateTimerEnd()
{
	if (!InstantShootWeapon)
	{
		PlayReloadSound();
	}
	else
	{
		CanShoot = true;
	}
}