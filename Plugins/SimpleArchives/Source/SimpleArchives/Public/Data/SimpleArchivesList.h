// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleArchivesList.generated.h"

USTRUCT()
struct SIMPLEARCHIVES_API FGameArchivesThumbnail
{
	GENERATED_USTRUCT_BODY()

		FGameArchivesThumbnail();

	UPROPERTY(Transient)
		UTexture2D* GameThumbnail;

	UPROPERTY(SaveGame)
		FString ScrPath;

	void InitResources();
	void ReleaseResources();
protected:
	void LoadTexture2D(const FString& ImagePath);
};

USTRUCT()
struct SIMPLEARCHIVES_API FSaveSlot
{
	GENERATED_USTRUCT_BODY()

	FSaveSlot();

	UPROPERTY(SaveGame)
		FGameArchivesThumbnail GameThumbnail;

	//�洢�����ݺ�����
	UPROPERTY(SaveGame)
		FText DateText;

	//�ؿ�����
	UPROPERTY(SaveGame)
		FText LevelName;

	//�½�����
	UPROPERTY(SaveGame)
		FText ChapterName;

	//�Ƿ�浵
	UPROPERTY(SaveGame)
		bool bSave;

	void Init();
};

USTRUCT()
struct SIMPLEARCHIVES_API FSaveSlotList
{
	GENERATED_USTRUCT_BODY()

		FSaveSlotList();

	//���ⲿ����
	void InitSlot();

	UPROPERTY(SaveGame)
		TMap<int32, FSaveSlot> Slots;

	UPROPERTY(SaveGame)
		TMap<int32, float> DegreeOfCompletion;

	int32 GetSerialNumber();

	bool RemoveAtGameData(int32 SlotNumber);
	bool AddGameDataByNumber(int32 SlotNumber);
};
