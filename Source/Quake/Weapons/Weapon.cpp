// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CanShoot = true;
}

// Called to configure class members replication
void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, CanShoot);
	
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

	// Player cam debug line
	//DrawDebugLine(GetWorld(), PlayerCamHit.TraceStart, PlayerCamHit.ImpactPoint, FColor::Orange, false, 2.0f);
	// Muzzle debug line
	//DrawDebugLine(GetWorld(), MuzzleHit.TraceStart, MuzzleHit.ImpactPoint, FColor::Red, true, 2.0f);

	return MuzzleHit;
}

void AWeapon::HandleFireRateTimerEnd()
{
	CanShoot = true;
}