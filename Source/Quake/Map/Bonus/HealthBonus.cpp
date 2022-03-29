// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBonus.h"

// Heal the player
void AHealthBonus::ApplyBonus(AQuakePlayer* Player)
{
	int HealToAdd = GetBonusAmount();

	Player->ServerAddHealth(HealToAdd);
}

// Returns RespawnTime value
float AHealthBonus::GetRespawnTime()
{
	return RespawnTime;
}

// Returns HealAmount value
int AHealthBonus::GetBonusAmount()
{
	return !Mega ? HealAmount : MegaHealAmount;
}