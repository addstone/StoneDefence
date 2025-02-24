// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../StoneDefenceType.h"
#include "PlayerSkillData.h"
#include "PlayerData.generated.h"

USTRUCT()
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()

	FPlayerData();

	void Init();

	bool IsValid();

	//玩家ID
	UPROPERTY(SaveGame)
		int32 PlayID;

	//玩家名字
	UPROPERTY(SaveGame)
		FName PlayName;

	//队伍
	UPROPERTY(SaveGame)
		TEnumAsByte<ETeam> Team;

	//玩家账户
	UPROPERTY(SaveGame)
		FString Account;

	//游戏金币
	UPROPERTY(SaveGame)
		int32 GameGold;

	//钻石 需要购买
	UPROPERTY(SaveGame)
		int32 Diamonds;

	//铜币 
	UPROPERTY(SaveGame)
		int32 Copper;

	UPROPERTY(SaveGame)
		float GameGoldTime;

	UPROPERTY(SaveGame)
		float MaxGameGoldTime;

	//玩家拥有的技能
	UPROPERTY(SaveGame)
		TArray<int32> SkillIDs;

	bool IsAllowIncrease();
};