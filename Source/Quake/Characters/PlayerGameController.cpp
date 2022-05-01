// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameController.h"

APlayerGameController::APlayerGameController()
{
	
}

void APlayerGameController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
}