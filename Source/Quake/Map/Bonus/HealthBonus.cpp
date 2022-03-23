// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBonus.h"

// Heal the player
void AHealthBonus::ApplyBonus()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HEAL"));
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