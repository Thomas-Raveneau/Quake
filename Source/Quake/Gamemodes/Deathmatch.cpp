// Fill out your copyright notice in the Description page of Project Settings.


#include "Deathmatch.h"

#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerStart.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

ADeathmatch::ADeathmatch()
{
	// Set default pawn class and HUD class
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_Player"));
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDCLass(TEXT("/Game/Blueprints/UI/HUD_Player"));

	if (PlayerPawnBPClass.Class != NULL)
		DefaultPawnClass = PlayerPawnBPClass.Class;
	if (PlayerHUDCLass.Class != NULL)
		HUDClass = PlayerHUDCLass.Class;

	bReplicates = true;
	SetReplicates(true);
}

void ADeathmatch::RespawnPlayer(AController* NewPlayer)
{
	AActor* randomPlayerStart = GetRandomPlayerStart();

	RestartPlayerAtPlayerStart(NewPlayer, randomPlayerStart);
}

void ADeathmatch::BeginPlay()
{
	Super::BeginPlay();

	//Bind our Player died delegate to the Gamemode's PlayerDied function.
	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &ADeathmatch::PlayerDied);
	}
}

AActor* ADeathmatch::GetRandomPlayerStart()
{
	TArray<AActor*> FoundPlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundPlayerStarts);
	int randomIndex;
	int nbTaken = 0;
	bool playerStartFound = false;

	for (int i = 0; i != FoundPlayerStarts.Num() - 1; i++) {
		if (FoundPlayerStarts[i]->Tags.Contains("Taken"))
			nbTaken += 1;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("NB TAKEN: %d"), nbTaken));

	while (!playerStartFound) {
		randomIndex = FMath::RandRange(0, FoundPlayerStarts.Num() - 1);

		if (!FoundPlayerStarts[randomIndex]->Tags.Contains("Taken")) {
			playerStartFound = true;
		}
		else {
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("TAKEN")));
		}
	}

	return FoundPlayerStarts[randomIndex];
}

void ADeathmatch::ServerDisablePlayerStart_Implementation(AActor* PlayerStart)
{
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	PlayerStart->Tags.Add("Taken");

	TimerDel.BindUFunction(this, FName("ServerEnablePlayerStart"), PlayerStart);
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 1.5f, false);
}

void ADeathmatch::ServerEnablePlayerStart_Implementation(AActor* PlayerStart)
{
	PlayerStart->Tags.Empty();
}

void ADeathmatch::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
}

void ADeathmatch::PlayerDied(ACharacter* Character)
{
	AActor* randomPlayerStart = GetRandomPlayerStart();
	AController* CharacterController = Character->GetController();

	ServerDisablePlayerStart(randomPlayerStart);
	RestartPlayerAtPlayerStart(CharacterController, randomPlayerStart);
}