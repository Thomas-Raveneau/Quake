// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerGameController.generated.h"

/**
 *
 */
UCLASS()
class QUAKE_API APlayerGameController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY()
		bool IsWindowFocused = false;

private:
	UPROPERTY()
		bool IsMenuOpened = false;

public:
	APlayerGameController();
	virtual ~APlayerGameController() = default;

	UFUNCTION(BlueprintCallable)
		void HandleMenuOpeningAndClosing(bool MenuOpening);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnWindowFocusChanged(bool IsFocused);
};
