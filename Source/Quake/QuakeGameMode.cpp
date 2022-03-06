// Copyright Epic Games, Inc. All Rights Reserved.


#include "QuakeGameMode.h"
#include "Characters/QuakePlayer.h"
#include "UObject/ConstructorHelpers.h"

AQuakeGameMode::AQuakeGameMode(): Super() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Player/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
}
