// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DeathmatchPlayerState.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DeathmatchState.generated.h"

/**
 * 
 */
UCLASS()
class QUAKE_API ADeathmatchState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ADeathmatchState();
	virtual ~ADeathmatchState() = default;

public:
	UFUNCTION(Server, Reliable)
		void ServerHandleKill(AController* Killer, AController* Killed);
};
