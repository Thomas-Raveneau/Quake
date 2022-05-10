// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserGunPoint.h"

// Give ammo to the player
void ALaserGunPoint::GiveAmmo(AQuakePlayer* Player)
{
	int AmmoToAdd = GetAmmoAmount();

	Player->ServerAddLaser(AmmoToAdd);
}

// Returns RespawnTime value
float ALaserGunPoint::GetRespawnTime()
{
	return RespawnTime;
}

// Returns AmmoAmount value
int ALaserGunPoint::GetAmmoAmount()
{
	return AmmoAmount;
}

