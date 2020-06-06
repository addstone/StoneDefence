// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleOfTheGameState.h"
#include "Kismet/GameplayStatics.h"
#include "../StoneDefenceUtils.h"
#include "../StoneDefenceType.h"

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

bool ARuleOfTheGameState::ClearGameData(int32 SaveNumber)
{
	if (FSaveSlot *InSlot = GetSaveSlot(SaveNumber))
	{
		//FString SlotName = FString::Printf(TEXT("SaveSlot_%i"), SaveNumber);
		//if (UGameplayStatics::DeleteGameInSlot(SlotName, 0))
		//{
			InSlot->Init();
			return true;
		//}
	}

	return false;
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
		SlotList = StoneDefenceUtils::GetSave<UGameSaveSlotList>(
			GetWorld(),
			TEXT("SlotList"),
			INDEX_NONE,
			EGameSaveType::ARCHIVES);
	}
	return SlotList;
}
