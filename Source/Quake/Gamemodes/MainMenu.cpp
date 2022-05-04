// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

AMainMenu::AMainMenu()
{
	static ConstructorHelpers::FClassFinder<AHUD> MenuHUDClass(TEXT("/Game/Blueprints/UI/Menus/MainMenu/HUD_MainMenu"));
	static ConstructorHelpers::FClassFinder<APlayerController> MenuControllerClass(TEXT("/Game/Blueprints/Player/BP_MenuController"));
	
	if (MenuHUDClass.Class != NULL)
	{
		HUDClass = MenuHUDClass.Class;
	}
	if (MenuControllerClass.Class != NULL) 
	{
		PlayerControllerClass = MenuControllerClass.Class;
	}
}