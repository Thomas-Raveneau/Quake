// Fill out your copyright notice in the Description page of Project Settings.


#include "Deathmatch.h"

#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerStart.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ADeathmatch::ADeathmatch()
{
	// Set default pawn class and HUD class
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_Player"));
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDCLass(TEXT("/Game/Blueprints/UI/HUD/HUD_Player"));

	if (PlayerPawnBPClass.Class != NULL)
		DefaultPawnClass = PlayerPawnBPClass.Class;
	if (PlayerHUDCLass.Class != NULL)
		HUDClass = PlayerHUDCLass.Class;
}

// Respawn the player
void ADeathmatch::RespawnPlayer(AController* NewPlayer)
{
	AActor* randomPlayerStart = GetRandomPlayerStart();

	RestartPlayerAtPlayerStart(NewPlayer, randomPlayerStart);
}

// Init on first frame
void ADeathmatch::BeginPlay()
{
	Super::BeginPlay();

	//Bind our Player died delegate to the Gamemode's PlayerDied function.
	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &ADeathmatch::PlayerDied);
	}
}

//Tries to Spawn the player's pawn
void ADeathmatch::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
}

// Return one random PlayerStart in current level
AActor* ADeathmatch::GetRandomPlayerStart()
{
	TArray<AActor*> FoundPlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundPlayerStarts);
	int randomIndex;
	bool playerStartFound = false;

	while (!playerStartFound) {
		randomIndex = FMath::RandRange(0, FoundPlayerStarts.Num() - 1);

		if (!FoundPlayerStarts[randomIndex]->Tags.Contains("Taken")) {
			playerStartFound = true;
		}
	}

	return FoundPlayerStarts[randomIndex];
}

// Disable passed PlayerStart
void ADeathmatch::ServerDisablePlayerStart_Implementation(AActor* PlayerStart)
{
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	PlayerStart->Tags.Add("Taken");

	TimerDel.BindUFunction(this, FName("ServerEnablePlayerStart"), PlayerStart);
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 1.5f, false);
}

// Enable passed PlayerStart
void ADeathmatch::ServerEnablePlayerStart_Implementation(AActor* PlayerStart)
{
	PlayerStart->Tags.Empty();
}

// Called when Player character has died
void ADeathmatch::PlayerDied(ACharacter* Character)
{
	AActor* randomPlayerStart = GetRandomPlayerStart();
	AController* CharacterController = Character->GetController();

	ServerDisablePlayerStart(randomPlayerStart);
	RestartPlayerAtPlayerStart(CharacterController, randomPlayerStart);
}