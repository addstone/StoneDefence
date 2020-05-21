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

	//�洢�����ݺ�����
	UPROPERTY(SaveGame)
		FText DateText;

	//��Ӧ�д浵�ĽǱ�
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
