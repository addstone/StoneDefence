#pragma once

#include "CoreMinimal.h"
#include "../StoneDefenceType.h"
#include "GameData.generated.h"

USTRUCT()
struct FGameInstanceDatas
{
	GENERATED_USTRUCT_BODY()

	FGameInstanceDatas();

	FSimpleOneInt32Delegate CallClientUpdate;

	void Init();

	//该关卡内存在最大多少怪物数量
	UPROPERTY(SaveGame)
		int32 MaxMonsters;

	//游戏难度有关
	UPROPERTY(SaveGame)
		uint8 GameDifficulty;

	//如果所有的主塔死亡,该值为true,并且禁止建造任何建筑
	UPROPERTY(SaveGame)
		uint8 bAllMainTowerDie : 1;

	//所有塔死亡,游戏结束
	UPROPERTY(Transient)
		uint8 bGameOver : 1;

	//所有塔死亡,则游戏结束
	UPROPERTY(Transient)
		uint8 bCurrentLevelMissionSuccess : 1;

	//当前关卡
	UPROPERTY(SaveGame)
		int32 CurrentLevel;

	//时间间隔（多久生成一次怪物）
	UPROPERTY(SaveGame)
		float TimeInterval;

	//生成怪物的时间记录
	UPROPERTY(SaveGame)
		float CurrentSpawnMosnterTime;

	//有多少波怪物
	UPROPERTY(SaveGame)
		int32 MaxStagesAreMonsters;

	//每波怪物当前数量 数量是动态
	UPROPERTY(SaveGame)
		TArray<int32> PerNumberOfMonsters;

	//总时间的倒计时
	UPROPERTY(SaveGame)
		float GameCount;

	//最大总时间的倒计时
	UPROPERTY(SaveGame)
		float MaxGameCount;

	//黄金产出的时间
	UPROPERTY(Transient)
		float GoldGrowthTime;

	//最大黄金产出的时间
	UPROPERTY(Transient)
		float GoldGrowthMaxTime;

	//杀死敌人总数量
	UPROPERTY(SaveGame)
		int32 KillMonstersNumber;

	//杀死Boss数量
	UPROPERTY(SaveGame)
		int32 KillMonsterBossNumber;

	//塔死亡总数
	UPROPERTY(SaveGame)
		int32 TowersDeathNumber;

	//主塔死亡数
	UPROPERTY(SaveGame)
		int32 MainTowersDeathNumber;

	float GetPerOfRemMonsters();

	int32 GetSurplusMonsters();

	void ResetSpawnMosnterTime();

	//每个阶段进行检测判定
	void StageDecision();

	//分配数量梯度，数量从少变多
	void AssignedMonsterAmount();

	FORCEINLINE bool IsAllowSpawnMosnter() { return CurrentSpawnMosnterTime >= TimeInterval; }
};

