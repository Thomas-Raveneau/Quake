// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"

// Default ABonus constructor
ABonus::ABonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the player activate the bonus
void ABonus::Activate()
{
	if (Active) {
		float RespawnTime = GetRespawnTime();

		BaseMesh->SetHiddenInGame(false);
		BonusMesh->SetHiddenInGame(true);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("TIME %f"), RespawnTime));
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABonus::Respawn, RespawnTime, false, RespawnTime);

		Active = false;
		ApplyBonus();
	}
}

// Called when the bonus needs to respawn after the respawn time is out
void ABonus::Respawn()
{
	BaseMesh->SetHiddenInGame(true);
	BonusMesh->SetHiddenInGame(false);

	Active = true;
}

// Returns RespawnTime values
float ABonus::GetRespawnTime()
{
	return 1.0f;
}

