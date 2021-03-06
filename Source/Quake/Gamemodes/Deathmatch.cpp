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

	PlayerControllerClass = APlayerGameController::StaticClass();
	GameStateClass = ADeathmatchState::StaticClass();
	PlayerStateClass = ADeathmatchPlayerState::StaticClass();
}

// Called to configure class members replication
void ADeathmatch::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADeathmatch, PlayersInGame);
}

// Respawn the player
void ADeathmatch::RespawnPlayer(AController* NewPlayer)
{
	AActor* randomPlayerStart = GetRandomPlayerStart();

	RestartPlayerAtPlayerStart(NewPlayer, randomPlayerStart);
}

void ADeathmatch::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayersInGame.Add(Cast<APlayerGameController>(NewPlayer));
}

void ADeathmatch::Logout(AController* ExitingController)
{
	Super::Logout(ExitingController);

	APlayerGameController* ExitingPlayer = Cast<APlayerGameController>(ExitingController);
	ADeathmatchState* DeathmatchState = Cast<ADeathmatchState>(GetWorld()->GetGameState());

	PlayersInGame.Empty();
	if (UWorld* world = GetWorld())
	{
		for (FConstPlayerControllerIterator PlayerControllerIterator = world->GetPlayerControllerIterator(); PlayerControllerIterator; PlayerControllerIterator++)
		{
			APlayerGameController* NewPlayer = Cast<APlayerGameController>(*PlayerControllerIterator);

			if (ExitingPlayer != NewPlayer)
			{
				PlayersInGame.Add(NewPlayer);
			}
		}
	}

	if (PlayersInGame.Num() <= 1)
		DeathmatchState->ServerHandleGameEnd();
}

// Init on first frame
void ADeathmatch::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* world = GetWorld())
	{
		for (FConstPlayerControllerIterator PlayerControllerIterator = world->GetPlayerControllerIterator(); PlayerControllerIterator; PlayerControllerIterator++)
		{
			APlayerGameController* NewPlayer = Cast<APlayerGameController>(*PlayerControllerIterator);

			PlayersInGame.Add(NewPlayer);
		}
	}

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

void ADeathmatch::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	AActor* randomPlayerStart = GetRandomPlayerStart();

	ServerDisablePlayerStart(randomPlayerStart);
	RestartPlayerAtPlayerStart(NewPlayer, randomPlayerStart);
}

// Return one random PlayerStart in current level
AActor* ADeathmatch::GetRandomPlayerStart()
{
	TArray<AActor*> FoundPlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundPlayerStarts);
	int randomIndex = 0;
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
	AQuakePlayer* QuakePlayer = Cast<AQuakePlayer>(Character);
	AActor* randomPlayerStart = GetRandomPlayerStart();
	AController* CharacterController = Character->GetController();

	if (QuakePlayer)
	{
		QuakePlayer->ServerDestroyLaser();
	}

	ServerDisablePlayerStart(randomPlayerStart);
	RestartPlayerAtPlayerStart(CharacterController, randomPlayerStart);
}