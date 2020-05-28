// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../StoneDefenceType.h"
#include "PlayerData.generated.h"



USTRUCT()
struct FPlayerSkillData
{
	GENERATED_BODY()

	FPlayerSkillData();

	void Init();

	bool IsValid();

	UPROPERTY(SaveGame)
		int32 SkillID;

	UPROPERTY(SaveGame)
		float SkillCD;

	UPROPERTY(SaveGame)
		float MaxSkillCD;

	UPROPERTY(SaveGame)
		int32 SkillNumber;
};


USTRUCT()
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()

	FPlayerData();

	void Init();

	bool IsValid();

	//���ID
	UPROPERTY(SaveGame)
		int32 PlayID;

	//�������
	UPROPERTY(SaveGame)
		FName PlayName;

	//����
	UPROPERTY(SaveGame)
		TEnumAsByte<ETeam> Team;

	//����˻�
	UPROPERTY(SaveGame)
		FString Account;

	//��Ϸ���
	UPROPERTY(SaveGame)
		int32 GameGold;

	//��ʯ ��Ҫ����
	UPROPERTY(SaveGame)
		int32 Diamonds;

	//ͭ�� 
	UPROPERTY(SaveGame)
		int32 Copper;

	UPROPERTY(SaveGame)
		float GameGoldTime;

	UPROPERTY(SaveGame)
		float MaxGameGoldTime;

	//���ӵ�еļ���
	UPROPERTY(SaveGame)
		TArray<int32> SkillIDs;

	//�����Ϸ������״̬
	UPROPERTY(SaveGame)
		TArray<FPlayerSkillData> SkillData;

	bool IsAllowIncrease();
};