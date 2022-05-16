// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserGun.h"

ALaserGun::ALaserGun()
{
	InstantShootWeapon = true;
}

float ALaserGun::GetFireRate() {
	return FireRate;
}