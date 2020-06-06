// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveSlotList.h"

void UGameSaveSlotList::InitSaveGame(UWorld *InWorld)
{
	SlotList.InitSlot();
}

void UGameSaveSlotList::InitSaveGameFromArchives(UWorld *InWorld)
{
	for (auto &Tmp : SlotList.Slots)
	{
		//Tmp.Value.GameThumbnail.InitResources();
	}
}