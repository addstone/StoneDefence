// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveSlotList.h"

#define LOCTEXT_NAMESPACE "SaveSlot"

FSaveSlot::FSaveSlot():
	DateText(LOCTEXT("SaveSlot", "Save slot hello world")),
	bSave(false)
{

}



FSaveSlotList::FSaveSlotList()
{
	for (int32 i = 0; i < 20; i++)
	{
		Slots.Add(i, FSaveSlot());
	}

	for (int32 i = 1; i < 6; i++)
	{
		DegreeOfCompletion.Add(i, 0.0f);
	}
}

int32 FSaveSlotList::GetSerialNumber()
{
	for (auto &Tmp : Slots)
	{
		if (!Tmp.Value.bSave)
		{
			return Tmp.Key;
		}
	}

	return INDEX_NONE;
}

bool FSaveSlotList::RemoveAtGameData(int32 SlotNumber)
{
	if (Slots.Contains(SlotNumber))
	{
		Slots[SlotNumber].bSave = false;
	}

	return false;
}

bool FSaveSlotList::AddGameDataByNumber(int32 SlotNumber)
{
	if (Slots.Contains(SlotNumber))
	{
		Slots[SlotNumber].bSave = true;
	}

	return false;
}

#undef LOCTEXT_NAMESPACE