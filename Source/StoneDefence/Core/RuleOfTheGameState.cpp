// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleOfTheGameState.h"
#include "Kismet/GameplayStatics.h"

ARuleOfTheGameState::ARuleOfTheGameState()
{

}

void ARuleOfTheGameState::BeginPlay()
{
	Super::BeginPlay();

	GetSaveSlotList().InitSlot();
}

FSaveSlotList & ARuleOfTheGameState::GetSaveSlotList()
{
	return GetGameSaveSlotList()->SlotList;
}

FSaveSlot * ARuleOfTheGameState::GetSaveSlot(int32 SaveNumber)
{
	if (GetSaveSlotList().Slots.Contains(SaveNumber))
	{
		return &GetSaveSlotList().Slots[SaveNumber];
	}

	return nullptr;
}

UGameSaveSlotList * ARuleOfTheGameState::GetGameSaveSlotList()
{
	if (!SlotList)
	{
		SlotList = Cast<UGameSaveSlotList>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot")), 0));
		if (!SlotList)
		{
			SlotList = Cast<UGameSaveSlotList>(UGameplayStatics::CreateSaveGameObject(UGameSaveSlotList::StaticClass()));
		}
	}
	return SlotList;
}
