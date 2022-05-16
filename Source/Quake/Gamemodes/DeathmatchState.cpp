// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathmatchState.h"

ADeathmatchState::ADeathmatchState()
{
}

void ADeathmatchState::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called to configure class members replication
void ADeathmatchState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADeathmatchState, GameTimerHandle);
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

void ADeathmatchState::ServerSetPlayerReadyToPlay_Implementation(AController* PlayerReady)
{
	int PlayerReadyCount = 0;
	ADeathmatchPlayerState * PlayerState = PlayerReady->GetPlayerState<ADeathmatchPlayerState>();


	if (PlayerState)
	{
		PlayerState->ReadyToPlay = true;
	}

	for (int i = 0; i != PlayerArray.Num(); i++)
	{
		ADeathmatchPlayerState* CurrentPlayerState = Cast<ADeathmatchPlayerState>(PlayerArray[i]);

		if (CurrentPlayerState->ReadyToPlay)
		{
			PlayerReadyCount++;
		}
	}


	if (PlayerReadyCount == PlayerArray.Num())
	{
		ServerStartGame();
	}
}

void ADeathmatchState::ServerStartGame_Implementation()
{
	for (int i = 0; i != PlayerArray.Num(); i++)
	{
		AQuakePlayer* PlayerPawn = Cast<AQuakePlayer>(PlayerArray[i]->GetPawn());

		if (PlayerPawn)
		{
			PlayerPawn->StartGame(GameDuration);
		}
	}

	GetWorldTimerManager().SetTimer(GameStartTimerHandle, this, &ADeathmatchState::ServerStartGameTimer, 3, false, 3);
}

void ADeathmatchState::ServerStartGameTimer_Implementation()
{
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ADeathmatchState::ServerHandleGameEnd, GameDuration, false, GameDuration);
}