// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/SaveGame.h"
#include "GameSaveSlotList.generated.h"

/**
 * 
 */
//UCLASS()
//class STONEDEFENCE_API UGameSaveSlotList : public USaveGame
//{
//	GENERATED_BODY()
//	
//};
USTRUCT()
struct FSaveSlot
{
	GENERATED_USTRUCT_BODY()

	FSaveSlot();

	//存储的内容和日期
	UPROPERTY(SaveGame)
		FText DateText;

	//对应有存档的角标
	UPROPERTY(SaveGame)
		int32 SaveGameBoxNumber;
};

USTRUCT()
struct FSaveSlotList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(SaveGame)
		TMap<int32, FSaveSlot> Slots;
};
