// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/SaveGameCore.h"
#include "../PlayerData.h"
#include "GameSaveData.h"
#include "../BuildingTowerData.h"
#include "PlayerSaveData.generated.h"






/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UPlayerSaveData : public USaveGameCore
{
	GENERATED_BODY()

public:
	//玩家数据
	UPROPERTY(SaveGame)
	FPlayerData PlayerData;

	//背包数据
	UPROPERTY(SaveGame)
	TMap<FGuid, FBuildingTower> BuildingTowers;

	////玩家游戏中数据的状态
	//UPROPERTY(SaveGame)
	//TMap<FGuid, FPlayerSkillData> PlayerSkillDatas;

	//virtual void InitSaveGame(UWorld *InWorld);

	//void AddPlayerSkill(UWorld *InWorld, const FGuid *Guid, int32 SkillID);
};
