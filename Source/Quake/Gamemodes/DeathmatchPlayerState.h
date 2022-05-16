// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "DeathmatchPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class QUAKE_API ADeathmatchPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, BlueprintReadWrite)
		int killCount = 0;
	UPROPERTY(Replicated, BlueprintReadWrite)
		int deathCount = 0;
	UPROPERTY(Replicated, BlueprintReadWrite)
		bool ReadyToPlay = false;
	
public:
	ADeathmatchPlayerState();
	virtual ~ADeathmatchPlayerState() = default;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable)
		void ServerAddKill();
	UFUNCTION(Server, Reliable)
		void ServerAddDeath();
};
