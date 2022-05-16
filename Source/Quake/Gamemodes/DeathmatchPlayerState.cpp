// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathmatchPlayerState.h"

ADeathmatchPlayerState::ADeathmatchPlayerState() 
{

}

void ADeathmatchPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADeathmatchPlayerState, killCount);
	DOREPLIFETIME(ADeathmatchPlayerState, deathCount);
	DOREPLIFETIME(ADeathmatchPlayerState, ReadyToPlay);
}

void ADeathmatchPlayerState::ServerAddKill_Implementation()
{
	killCount += 1;
}

void ADeathmatchPlayerState::ServerAddDeath_Implementation()
{
	deathCount += 1;
}
