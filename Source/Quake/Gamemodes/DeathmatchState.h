// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Deathmatch.h"
#include "DeathmatchPlayerState.h"
#include "../Characters/QuakePlayer.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DeathmatchState.generated.h"

// Game settings
#define GAME_DURATION 150.0f
#define GAME_START_ANIMATION_DURATION 6.5f

UCLASS()
class QUAKE_API ADeathmatchState : public AGameStateBase
{
	GENERATED_BODY()

public:
	//Game timer handler
	UPROPERTY(Replicated, BlueprintReadOnly)
		FTimerHandle GameTimerHandle;
	UPROPERTY()
		FTimerHandle GameStartTimerHandle;
	UPROPERTY()
		FTimerHandle GameEndTimerHandle;

	UPROPERTY(BlueprintReadOnly)
		float GameDuration = GAME_DURATION;

public:
	ADeathmatchState();
	virtual ~ADeathmatchState() = default;

	virtual void BeginPlay() override;

	// Called to configure class members replication
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable)
		void ServerHandleKill(AController* Killer, AController* Killed);

	UFUNCTION(Server, Reliable)
		void ServerHandleGameEnd();

	UFUNCTION()
		APlayerState* GetGameWinner();

	UFUNCTION(Server, Reliable)
		void ServerTravelToLobby();

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void ServerSetPlayerReadyToPlay(AController* PlayerReady);

	UFUNCTION(Server, Reliable)
		void ServerStartGame();

	UFUNCTION(Server, Reliable)
		void ServerStartGameTimer();
};
