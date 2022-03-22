// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldBonus.h"

void AShieldBonus::ApplyBonus()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("SHIELD"));
}

float AShieldBonus::GetRespawnTime()
{
	return RespawnTime;
}
