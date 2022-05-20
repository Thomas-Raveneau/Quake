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
	APlayerState* GameWinner = GetGameWinner();

	for (int i = 0; i != PlayerArray.Num(); i++)
	{
		//ADeathmatchPlayerState* PlayerState
		AQuakePlayer* PlayerPawn = Cast<AQuakePlayer>(PlayerArray[i]->GetPawn());

		if (PlayerPawn)
		{
			if (PlayerArray[i] == GameWinner)
			{
				PlayerPawn->EndGame(true);
			}
			else 
			{
				PlayerPawn->EndGame(false);
			}
		}
	}

	GetWorldTimerManager().SetTimer(GameEndTimerHandle, this, &ADeathmatchState::ServerTravelToLobby, 5, false, 5);
}

APlayerState* ADeathmatchState::GetGameWinner()
{
	APlayerState* GameWinner = nullptr;
	int GameWinnerMaxKill = -1;

	for (int i = 0; i != PlayerArray.Num(); i++)
	{
		ADeathmatchPlayerState* PlayerState = Cast<ADeathmatchPlayerState>(PlayerArray[i]);
		
		if (PlayerState)
		{
			if (PlayerState->killCount > GameWinnerMaxKill)
			{
				GameWinner = PlayerArray[i];
				GameWinnerMaxKill = PlayerState->killCount;
			}
		}
	}

	return GameWinner;
}

void ADeathmatchState::ServerTravelToLobby_Implementation()
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

	GetWorldTimerManager().SetTimer(GameStartTimerHandle, this, &ADeathmatchState::ServerStartGameTimer, GAME_START_ANIMATION_DURATION, false, GAME_START_ANIMATION_DURATION);
}

void ADeathmatchState::ServerStartGameTimer_Implementation()
{
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ADeathmatchState::ServerHandleGameEnd, GameDuration, false, GameDuration);
}