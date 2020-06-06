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
	//游戏场景中的角色
	UPROPERTY(SaveGame)
		TMap<FGuid, FCharacterData> CharacterDatas;

	//当前关卡内游戏数据
	UPROPERTY(SaveGame)
		FGameInstanceDatas GamerDatas;

	virtual void InitSaveGame(UWorld *InWorld);
};
