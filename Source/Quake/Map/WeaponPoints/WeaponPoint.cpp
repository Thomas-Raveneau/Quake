// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPoint.h"

// Sets default values
AWeaponPoint::AWeaponPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the player activate the point
void AWeaponPoint::Activate(AQuakePlayer* Player)
{
	if (Active) {
		if (!WeaponMesh) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Set WeaponMesh property in WeaponPoint blueprints"));
			return;
		}

		float RespawnTime = GetRespawnTime();

		WeaponMesh->SetHiddenInGame(true);

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AWeaponPoint::Respawn, RespawnTime, false, RespawnTime);

		Active = false;
		GiveAmmo(Player);
	}
}

// Called when the bonus needs to respawn after the respawn time is out
void AWeaponPoint::Respawn()
{
	if (!WeaponMesh) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Set WeaponMesh property in WeaponPoint blueprints"));
		return;
	}
	WeaponMesh->SetHiddenInGame(false);

	Active = true;
}
