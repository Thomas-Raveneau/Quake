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
	ADeathmatch();

	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	void RespawnPlayer(AController* NewPlayer);

protected:
	virtual void BeginPlay() override;

	//Tries to Spawn the player's pawn.
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* PlayerStart) override;

	UFUNCTION()
		AActor* GetRandomPlayerStart();

	UFUNCTION(Server, Reliable)
		void ServerDisablePlayerStart(AActor* PlayerStart);

	UFUNCTION(Server, Reliable)
		void ServerEnablePlayerStart(AActor* PlayerStart);

	//Called when Player character has died.
	UFUNCTION()
		virtual void PlayerDied(ACharacter* Character);

	//Signature to bind delegate. 
	UPROPERTY()
		FOnPlayerDiedSignature OnPlayerDied;
};
