// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
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
	// Constuctor
	ADeathmatch();

public:
	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	// Respawn the player
	void RespawnPlayer(AController* NewPlayer);

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

	// Signature to bind delegate
	UPROPERTY()
		FOnPlayerDiedSignature OnPlayerDied;
};
