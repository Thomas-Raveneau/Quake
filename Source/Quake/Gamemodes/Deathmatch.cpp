// Fill out your copyright notice in the Description page of Project Settings.


#include "Deathmatch.h"

ADeathmatch::ADeathmatch() 
{
    // Set default pawn class and HUD class
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_Player"));
    static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDCLass(TEXT("/Game/Blueprints/UI/HUD_Player"));

    if (PlayerPawnBPClass.Class != NULL)
        DefaultPawnClass = PlayerPawnBPClass.Class;
    if (PlayerHUDCLass.Class != NULL)
        HUDClass = PlayerHUDCLass.Class;
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

void ADeathmatch::RestartPlayer(AController* NewPlayer)
{
    Super::RestartPlayer(NewPlayer);
}

void ADeathmatch::PlayerDied(ACharacter* Character)
{
    //Get a reference to our Character's Player Controller
    AController* CharacterController = Character->GetController();
    RestartPlayer(CharacterController);
}