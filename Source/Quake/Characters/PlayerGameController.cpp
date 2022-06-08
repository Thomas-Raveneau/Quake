// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameController.h"

APlayerGameController::APlayerGameController()
{

}

void APlayerGameController::HandleMenuOpeningAndClosing(bool MenuOpening)
{
	if (!MenuOpening) {
		IsMenuOpened = false;

		FInputModeGameOnly InputMode;

		SetInputMode(InputMode);
		SetShowMouseCursor(false);
	}
	else
	{
		IsMenuOpened = true;

		FInputModeUIOnly InputMode;

		SetInputMode(InputMode);
		SetShowMouseCursor(true);
	}
}

void APlayerGameController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld()->IsServer())
	{
		FSlateApplication::Get().OnApplicationActivationStateChanged()
			.AddUObject(this, &APlayerGameController::OnWindowFocusChanged);
	}
}

void APlayerGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputModeGameOnly InputMode;

	SetInputMode(InputMode);
	SetShowMouseCursor(false);
	IsWindowFocused = true;
}

void APlayerGameController::Tick(float DeltaSeconds)
{
	if (IsWindowFocused && !IsMenuOpened) {
		int x = 0;
		int y = 0;

		GetViewportSize(x, y);
		SetMouseLocation(x / 2, y / 2);
	}
}

void APlayerGameController::OnWindowFocusChanged(bool IsFocused)
{
	IsWindowFocused = IsFocused;
}