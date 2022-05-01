// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathmatchState.h"

ADeathmatchState::ADeathmatchState()
{
	//GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ADeathmatchState::GameTimerEnded, GAME_DURATION, false, GAME_DURATION);
}

void ADeathmatchState::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ADeathmatchState::ServerHandleGameEnd, GAME_DURATION, false, GAME_DURATION);
}

void ADeathmatchState::ServerHandleKill_Implementation(AController* Killer, AController* Killed)
{
	Killed->GetPlayerState<ADeathmatchPlayerState>()->ServerAddDeath();

	if (Killer != Killed)
		Killer->GetPlayerState<ADeathmatchPlayerState>()->ServerAddKill();
}

void ADeathmatchState::ServerHandleGameEnd_Implementation()
{
	GetWorld()->ServerTravel(TEXT("/Game/Levels/SessionLobby"));
}
