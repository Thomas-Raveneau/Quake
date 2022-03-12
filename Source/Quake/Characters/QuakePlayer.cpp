// Fill out your copyright notice in the Description page of Project Settings.


#include "QuakePlayer.h"

// Sets default values
AQuakePlayer::AQuakePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuakePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuakePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Pos %f"), PlayerPos.Y));
}

// Called to bind functionality to input
void AQuakePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AQuakePlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AQuakePlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AQuakePlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AQuakePlayer::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AQuakePlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AQuakePlayer::StopJumping);
}

void AQuakePlayer::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AQuakePlayer::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AQuakePlayer::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AQuakePlayer::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}