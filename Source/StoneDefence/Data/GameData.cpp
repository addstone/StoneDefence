#include "GameData.h"

FGameInstanceDatas::FGameInstanceDatas()
{
	Init();
}

void FGameInstanceDatas::Init()
{
	MaxMonsters = 100;
	GameDifficulty = 0;
	bAllMainTowerDie = false;
	bGameOver =false;
	bCurrentLevelMissionSuccess = false;
	CurrentLevel = INDEX_NONE;
	TimeInterval = 4.f;
	CurrentSpawnMosnterTime = 0.f;
	MaxStagesAreMonsters = 4;
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
	if (MaxMonsters != 0)
	{
		return (float)GetSurplusMonsters() / (float)MaxMonsters;
	}

	return 0.f;
}

int32 FGameInstanceDatas::GetSurplusMonsters()
{
	int32 InSurplus = 0;
	for (auto &Tmp : PerNumberOfMonsters)
	{
		InSurplus += Tmp;
	}

	return InSurplus;
}

void FGameInstanceDatas::ResetSpawnMosnterTime()
{
	CurrentSpawnMosnterTime = 0.0f;
}

void FGameInstanceDatas::StageDecision()
{
	int32 CurrentStagesAreMonsters = PerNumberOfMonsters.Num() - 1;
	if (PerNumberOfMonsters.Num())
	{
		if (PerNumberOfMonsters[CurrentStagesAreMonsters] > 0)
		{
			PerNumberOfMonsters[CurrentStagesAreMonsters]--;
		}
		else
		{
			PerNumberOfMonsters.RemoveAt(CurrentStagesAreMonsters);
		}
	}
	else
	{
		bCurrentLevelMissionSuccess = true;
	}
}

void FGameInstanceDatas::AssignedMonsterAmount()
{
	//多少的怪物
	int32 CurrentMonsterNumber = MaxMonsters;

	//最大阶段
	int32 CurrentStagesNumber = MaxStagesAreMonsters;

	//每阶段的数量
	int32 CurrentAssignedNum = 0;

	if (CurrentMonsterNumber > 1)
	{
		for (int32 i = 0; i < MaxStagesAreMonsters; i++) //每阶段
		{
			//每阶段的平均值
			float StagesNumber = (float)CurrentMonsterNumber / (float)CurrentStagesNumber;

			//减去该阶段
			CurrentStagesNumber--;
			if (CurrentStagesNumber > 0)
			{
				//随机阶段，从平均值一般到平均值分配
				CurrentAssignedNum = FMath::RandRange(StagesNumber / 6, StagesNumber);
			}
			else
			{
				CurrentAssignedNum = StagesNumber;
			}

			PerNumberOfMonsters.Add(CurrentAssignedNum);

			//减去分配的数量
			CurrentMonsterNumber -= CurrentAssignedNum;
		}
	}
	else
	{
		PerNumberOfMonsters.Add(CurrentAssignedNum);
	}
}
