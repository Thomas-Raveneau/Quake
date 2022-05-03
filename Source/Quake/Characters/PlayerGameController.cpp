// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameController.h"

APlayerGameController::APlayerGameController()
{

}

void APlayerGameController::BeginPlay()
{
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
	if (IsWindowFocused) {
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