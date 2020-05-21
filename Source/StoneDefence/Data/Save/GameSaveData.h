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
	//��Ϸ�����еĽ�ɫ
	UPROPERTY()
		TMap<uint32, FCharacterData> CharacterDatas;
};
