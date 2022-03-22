// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBonus.h"

void AHealthBonus::ApplyBonus()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HEAL"));
}

float AHealthBonus::GetRespawnTime()
{
	return RespawnTime;
}