// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathmatchState.h"

ADeathmatchState::ADeathmatchState()
{
	
}

void ADeathmatchState::ServerHandleKill_Implementation(AController* Killer, AController* Killed)
{
	Killed->GetPlayerState<ADeathmatchPlayerState>()->ServerAddDeath();

	if (Killer != Killed)
		Killer->GetPlayerState<ADeathmatchPlayerState>()->ServerAddKill();
}
