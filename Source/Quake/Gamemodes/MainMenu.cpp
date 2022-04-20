// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

AMainMenu::AMainMenu()
{
	static ConstructorHelpers::FClassFinder<AHUD> MenuHUDCLass(TEXT("/Game/Blueprints/UI/Menus/MainMenu/HUD_MainMenu"));
	static ConstructorHelpers::FClassFinder<APlayerController> MenuControllerCLass(TEXT("/Game/Blueprints/Player/BP_MenuController"));
	
	if (MenuHUDCLass.Class != NULL)
	{
		HUDClass = MenuHUDCLass.Class;
	}
	if (MenuControllerCLass.Class != NULL) 
	{
		PlayerControllerClass = MenuControllerCLass.Class;
	}
}