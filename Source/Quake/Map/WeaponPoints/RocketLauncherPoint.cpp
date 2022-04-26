// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLauncherPoint.h"

// Give ammo to the player
void ARocketLauncherPoint::GiveAmmo(AQuakePlayer* Player)
{
	int AmmoToAdd = GetAmmoAmount();

	Player->ServerAddRocket(AmmoToAdd);
}

// Returns RespawnTime value
float ARocketLauncherPoint::GetRespawnTime()
{
	return RespawnTime;
}

// Returns AmmoAmount value
int ARocketLauncherPoint::GetAmmoAmount()
{
	return AmmoAmount;
}