// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../CharacterData.h"
#include "GameSaveData.generated.h"

USTRUCT()
struct FBuildingTower
{
	GENERATED_BODY()

	//需要的消费金币
	UPROPERTY(SaveGame)
		int32 NeedGold;

	//准备阶段塔建造数量
	UPROPERTY(SaveGame)
		int32 TowersPerpareBuildingNumber;

	//塔已经建造数量
	UPROPERTY(SaveGame)
		int32 TowersConstructionNumber;

	//当前塔最大建造CD
	UPROPERTY(SaveGame)
		float MaxConstructionTowersCD;

	//当前建造中塔的CD
	UPROPERTY(SaveGame)
		float CurrentConstrictionTowersCD;

	//作为ICO指针
	UPROPERTY(SaveGame)
		UTexture2D* ICO;

	//是否拖拽图标
	UPROPERTY(SaveGame)
		bool bDragICO;

	//锁
	UPROPERTY(SaveGame)
		bool bLockCD;

	UPROPERTY(SaveGame)
		bool bCallUpdateTowersInfo;
};
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UGameSaveData : public USaveGame
{
	GENERATED_BODY()
public:
	//游戏场景中的角色
	UPROPERTY(SaveGame)
		TMap<FGuid, FCharacterData> CharacterDatas;

	UPROPERTY(SaveGame)
	TMap <FGuid, FBuildingTower> BuildingTowers;
};
