// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLauncher.h"

ARocketLauncher::ARocketLauncher()
{
	InstantShootWeapon = false;
}

// Returns fire rate value
float ARocketLauncher::GetFireRate()
{
	return FireRate;
}