// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameController.h"

APlayerGameController::APlayerGameController()
{

}

void APlayerGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputModeGameOnly InputMode;

	SetInputMode(InputMode);
	SetShowMouseCursor(false);
}

void APlayerGameController::Tick(float DeltaSeconds)
{
	int x = 0;
	int y = 0;

	GetViewportSize(x, y);
	SetMouseLocation(x / 2, y / 2);
}