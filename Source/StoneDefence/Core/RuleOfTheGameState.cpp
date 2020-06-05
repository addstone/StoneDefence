// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleOfTheGameState.h"
#include "Kismet/GameplayStatics.h"

ARuleOfTheGameState::ARuleOfTheGameState()
{

}

void ARuleOfTheGameState::BeginPlay()
{

}

FSaveSlotList & ARuleOfTheGameState::GetSaveSlotList()
{
	return GetGameSaveSlotList()->SlotList;
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
