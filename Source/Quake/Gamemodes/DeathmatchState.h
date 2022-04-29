// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DeathmatchPlayerState.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DeathmatchState.generated.h"

// Game settings
#define GAME_DURATION 600.0f

UCLASS()
class QUAKE_API ADeathmatchState : public AGameStateBase
{
	GENERATED_BODY()

private:
	//Game timer handler
	UPROPERTY()
		FTimerHandle GameTimerHandle;

public:
	ADeathmatchState();
	virtual ~ADeathmatchState() = default;

	virtual void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable)
		void ServerHandleKill(AController* Killer, AController* Killed);

	UFUNCTION(Server, Reliable)
		void ServerHandleGameEnd();
};
