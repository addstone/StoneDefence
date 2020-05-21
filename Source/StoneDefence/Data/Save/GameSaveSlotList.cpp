// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaveSlotList.h"

#define LOCTEXT_NAMESPACE "SaveSlot"

FSaveSlot::FSaveSlot():
	DateText(LOCTEXT("SaveSlot", "Save slot hello world")),
	SaveGameBoxNumber(INDEX_NONE)
{

}

#undef LOCTEXT_NAMESPACE