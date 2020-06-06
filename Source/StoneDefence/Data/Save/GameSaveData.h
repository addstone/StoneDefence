// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../CharacterData.h"
#include "../PlayerData.h"
#include "../GameData.h"
#include "GameSaveData.generated.h"



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

	//��ǰ�ؿ�����Ϸ����
	UPROPERTY(SaveGame)
		FGameInstanceDatas GamerDatas;

	virtual void InitSaveGame(UWorld *InWorld);
};
