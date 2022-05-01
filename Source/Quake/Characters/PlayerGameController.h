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
	APlayerGameController();
	virtual ~APlayerGameController() = default;

protected:
	virtual void BeginPlay() override;
};
