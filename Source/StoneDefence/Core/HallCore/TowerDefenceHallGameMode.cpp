// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceHallGameMode.h"
#include "TowerDefenceHallPawn.h"
#include "../../UI/HallUI/Core/TowersDefenceHallHUD.h"
#include "TowerDefenceHallGameState.h"
#include "../RuleOfThePlayerState.h"
#include "TowerDefenceHallPlayerController.h"

ATowerDefenceHallGameMode::ATowerDefenceHallGameMode()
{
	DefaultPawnClass = ATowerDefenceHallPawn::StaticClass();
	HUDClass = ATowersDefenceHallHUD::StaticClass();
	GameStateClass = ATowerDefenceHallGameState::StaticClass();
	PlayerStateClass = ARuleOfThePlayerState::StaticClass();
	PlayerControllerClass = ATowerDefenceHallPlayerController::StaticClass();
}
