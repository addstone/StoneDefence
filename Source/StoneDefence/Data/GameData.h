#pragma once

#include "CoreMinimal.h"
#include "GameData.generated.h"

USTRUCT()
struct FGameInstanceDatas
{
	GENERATED_USTRUCT_BODY()

	FGameInstanceDatas();

	void Init();

	//�ùؿ��ڹ�������
	UPROPERTY()
		int32 NumberOfMonster;

	//��Ϸ�Ѷ��й�
	UPROPERTY(SaveGame)
		uint8 GameDifficulty;

	//������е���������,��ֵΪtrue,���ҽ�ֹ�����κν���
	UPROPERTY(SaveGame)
		uint8 bAllMainTowerDie : 1;

	//����������,��Ϸ����
	UPROPERTY(Transient)
		uint8 bGameOver : 1;

	//����������,����Ϸ����
	UPROPERTY(Transient)
		uint8 bCurrentLevelMissionSuccess : 1;

	//���ɹ���׶�
	UPROPERTY(SaveGame)
		uint8 SpawnMonsterStage;

	//��ǰ�ؿ�
	UPROPERTY(SaveGame)
		int32 CurrentLevel;

	//ʱ�������������һ�ι��
	UPROPERTY(SaveGame)
		float TimeInterval;

	//�ж��ٲ�����
	UPROPERTY(SaveGame)
		int32 MaxStagesAreMonsters;

	//��ǰ����һ������
	UPROPERTY(SaveGame)
		int32 CurrentStageAreMonsters;

	//ÿ�����ﵱǰ���� �����Ƕ�̬
	UPROPERTY(SaveGame)
		TArray<int32> PerNumberOfMonsters;

	//��ʱ��ĵ���ʱ
	UPROPERTY(SaveGame)
		float GameCount;

	//�����ʱ��ĵ���ʱ
	UPROPERTY(SaveGame)
		float MaxGameCount;

	//�ƽ������ʱ��
	UPROPERTY(Transient)
		float GoldGrowthTime;

	//���ƽ������ʱ��
	UPROPERTY(Transient)
		float GoldGrowthMaxTime;

	//ɱ������������
	UPROPERTY(SaveGame)
		int32 KillMonstersNumber;

	//ɱ��Boss����
	UPROPERTY(SaveGame)
		int32 KillMonsterBossNumber;

	//����������
	UPROPERTY(SaveGame)
		int32 TowersDeathNumber;

	//����������
	UPROPERTY(SaveGame)
		int32 MainTowersDeathNumber;


};

