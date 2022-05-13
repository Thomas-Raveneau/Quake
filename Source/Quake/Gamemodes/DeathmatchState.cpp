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
	UE_LOG(LogClass, Log, TEXT("ServerSetPlayerReadyToPlay CALLED"));

	ADeathmatchPlayerState * PlayerState = PlayerReady->GetPlayerState<ADeathmatchPlayerState>();

	if (PlayerState)
	{
		PlayerState->ReadyToPlay = true;
		UE_LOG(LogClass, Log, TEXT("PLAYER STATE OK"));
	}
	else 
	{
		UE_LOG(LogClass, Log, TEXT("NO PLAYER STATE"));
	}

	int PlayerReadyCount = 0;

	for (int i = 0; i != PlayerArray.Num(); i++)
	{
		ADeathmatchPlayerState* CurrentPlayerState = Cast<ADeathmatchPlayerState>(PlayerArray[i]);

		UE_LOG(LogClass, Log, TEXT("PLAYER CHECK"));

		if (CurrentPlayerState->ReadyToPlay)
		{
			PlayerReadyCount++;
			UE_LOG(LogClass, Log, TEXT("PLAYER COUNT ++"));
		}
	}

	UE_LOG(LogClass, Log, TEXT("PLAYER COUNT OK"));

	if (PlayerReadyCount == PlayerArray.Num())
	{
		UE_LOG(LogClass, Log, TEXT("CHECK OK"));
			
		ADeathmatch* Gamemode = Cast<ADeathmatch>(GetWorld()->GetAuthGameMode());
		UE_LOG(LogClass, Log, TEXT("TEST"));

		if (Gamemode)
		{
			UE_LOG(LogClass, Log, TEXT("GAMEMODE OK"));
			Gamemode->ServerStartGame(GameDuration);
			UE_LOG(LogClass, Log, TEXT("GAMEMODE START OK"));
		}
		else {
			UE_LOG(LogClass, Log, TEXT("NO GAMEMODE"));
		}
	}
}