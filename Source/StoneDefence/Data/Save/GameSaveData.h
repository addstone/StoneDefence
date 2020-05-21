// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../CharacterData.h"
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
	UPROPERTY()
		TMap<uint32, FCharacterData> CharacterDatas;
};
