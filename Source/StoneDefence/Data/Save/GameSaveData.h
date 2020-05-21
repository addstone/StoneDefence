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

	//��Ҫ�����ѽ��
	UPROPERTY(SaveGame)
		int32 NeedGold;

	//׼���׶�����������
	UPROPERTY(SaveGame)
		int32 TowersPerpareBuildingNumber;

	//���Ѿ���������
	UPROPERTY(SaveGame)
		int32 TowersConstructionNumber;

	//��ǰ�������CD
	UPROPERTY(SaveGame)
		float MaxConstructionTowersCD;

	//��ǰ����������CD
	UPROPERTY(SaveGame)
		float CurrentConstrictionTowersCD;

	//��ΪICOָ��
	UPROPERTY(SaveGame)
		UTexture2D* ICO;

	//�Ƿ���קͼ��
	UPROPERTY(SaveGame)
		bool bDragICO;

	//��
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
	//��Ϸ�����еĽ�ɫ
	UPROPERTY(SaveGame)
		TMap<FGuid, FCharacterData> CharacterDatas;

	UPROPERTY(SaveGame)
	TMap <FGuid, FBuildingTower> BuildingTowers;
};
