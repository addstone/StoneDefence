// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "StoneDefenceGameModeBase.h"
#include "Core/GameCore/TowersDefenceGameState.h"
#include "Core/GameCore/TowersDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"
#include "Core/GameCore/TowersDefencePlayerState.h"
#include "UI/GameUI/Core/RuleofTheHUD.h"
#include "StoneDefenceUtils.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Character/CharacterCore/Towers.h"

AStoneDefenceGameModeBase::AStoneDefenceGameModeBase()
{
	GameStateClass = ATowersDefenceGameState::StaticClass();
	PlayerControllerClass = ATowersDefencePlayerController::StaticClass();
	DefaultPawnClass = ATowerDefenceGameCamera::StaticClass();
	PlayerStateClass = ATowersDefencePlayerState::StaticClass();
	HUDClass = ARuleofTheHUD::StaticClass();
}

void ATowersDefenceGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ATowersDefenceGameState *InGameState = GetWorld()->GetGameState<ATowersDefenceGameState>())
	{
		GetPlayerData().GameGoldTime += DeltaSeconds;

		if (GetPlayerData().IsAllowIncrease())
		{
			GetPlayerData().GameGoldTime = 0;
			GetPlayerData().GameGold++;
		}


		if (InGameState->GetGameData().GameCount <= 0.f)
		{
			InGameState->GetGameData().bGameOver = true;
		}
		else
		{
			InGameState->GetGameData().GameCount -= DeltaSeconds;
		}
		int32 TowersNum = 0;
		TArray<ARuleOfTheCharacter*> InTowers;
		StoneDefenceUtils::GetAllActor<ATowers>(GetWorld(), InTowers);
		for (ARuleOfTheCharacter* Tower : InTowers)
		{
			if (Tower->IsActive())
			{
				TowersNum++;
			}
		}
		if (TowersNum == 0)
		{
			InGameState->GetGameData().bGameOver = true;
		}
		//Éú³É¹ÖÎï
		InGameState->SpawnMonstersRule(DeltaSeconds);
	}

	
}
