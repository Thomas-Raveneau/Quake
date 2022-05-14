// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DeathmatchState.h"
#include "DeathmatchPlayerState.h"
#include "../Characters/QuakePlayer.h"
#include "../Characters/PlayerGameController.h"

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/HUD.h"
#include "GameFramework/Character.h"
#include "Deathmatch.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);

UCLASS()
class QUAKE_API ADeathmatch : public AGameModeBase
{

	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Replicated)
		TArray<APlayerGameController*> PlayersInGame;

public:
	// Constuctor
	ADeathmatch();

	// Called to configure class members replication
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	// Respawn the player
	void RespawnPlayer(AController* NewPlayer);
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* ExitingController) override;

protected:
	// Init on first frame
	virtual void BeginPlay() override;

	// Tries to Spawn the player's pawn
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* PlayerStart) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	// Return one random PlayerStart in current level
	UFUNCTION()
		AActor* GetRandomPlayerStart();

	// Disable passed PlayerStart
	UFUNCTION(Server, Reliable)
		void ServerDisablePlayerStart(AActor* PlayerStart);

	// Enable passed PlayerStart
	UFUNCTION(Server, Reliable)
		void ServerEnablePlayerStart(AActor* PlayerStart);

	// Called when Player character has died
	UFUNCTION()
		virtual void PlayerDied(ACharacter* Character);

protected:
	// Signature to bind delegate
	UPROPERTY()
		FOnPlayerDiedSignature OnPlayerDied;
};
