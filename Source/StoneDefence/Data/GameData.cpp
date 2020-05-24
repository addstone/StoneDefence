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
	MaxStagesAreMonsters = 0;
	CurrentStageAreMonsters = 0;
	GameCount = 0;
	MaxGameCount = 0;
	GoldGrowthTime = 1.f;
	GoldGrowthMaxTime = 1.5f;
	KillMonstersNumber = 0;
	KillMonsterBossNumber = 0;
	TowersDeathNumber = 0;
	MainTowersDeathNumber = 0;
}
