// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBonus.h"

void AShieldBonus::ApplyBonus(AQuakePlayer* Player)
{
	int ShieldToAdd = GetBonusAmount();

	Player->ServerAddShield(ShieldToAdd);
}

float AShieldBonus::GetRespawnTime()
{
	return RespawnTime;
}

// Returns ShieldAmount value
int AShieldBonus::GetBonusAmount()
{
	return !Mega ?ShieldAmount : MegaShieldAmount;
}
