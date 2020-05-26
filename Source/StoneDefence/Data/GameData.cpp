#include "GameData.h"

FGameInstanceDatas::FGameInstanceDatas()
{
	Init();
}

void FGameInstanceDatas::Init()
{
	NumberOfMonster = 0;
	GameDifficulty = 0;
	bAllMainTowerDie = false;
	bGameOver =false;
	bCurrentLevelMissionSuccess = false;
	SpawnMonsterStage = 0;
	CurrentLevel = INDEX_NONE;
	TimeInterval = 0.5f;
	CurrentSpawnMosnterTime = 0.f;
	MaxStagesAreMonsters = 0;
	CurrentStageAreMonsters = 0;
	GameCount = 6000;
	MaxGameCount = 0;
	GoldGrowthTime = 1.f;
	GoldGrowthMaxTime = 1.5f;
	KillMonstersNumber = 0;
	KillMonsterBossNumber = 0;
	TowersDeathNumber = 0;
	MainTowersDeathNumber = 0;
}

float FGameInstanceDatas::GetPerOfRemMonsters()
{
	int32 MaxMonstersNumber = GetMaxMonstersNumber();
	if (MaxMonstersNumber != 0)
	{
		return (float)NumberOfMonster / (float)MaxMonstersNumber;
	}

	return 0.f;
}

int32 FGameInstanceDatas::GetMaxMonstersNumber()
{
	int32 MaxMonstersNumber = 0;
	for (auto &Tmp : PerNumberOfMonsters)
	{
		MaxMonstersNumber += Tmp;
	}
	return MaxMonstersNumber;
}

void FGameInstanceDatas::ResetSpawnMosnterTime()
{
	CurrentSpawnMosnterTime = 0.0f;
}
