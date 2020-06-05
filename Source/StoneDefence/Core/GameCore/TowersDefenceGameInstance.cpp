// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceGameInstance.h"
#include "Modules/ModuleManager.h"
#include "SimpleScreenLoading.h"
#include "../RuleOfTheGameState.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "TowerGameInstance"

UTowersDefenceGameInstance::UTowersDefenceGameInstance()
	:ISimpleArchivesInterface()
{

}

int32 UTowersDefenceGameInstance::GetSaveSlotNumber() const
{
	int32 SlotNumber = 20;
	if (ARuleOfTheGameState *InGameState = GetGameState())
	{
		SlotNumber = InGameState->GetSaveSlotList().Slots.Num();
	}

	return SlotNumber;
}

bool UTowersDefenceGameInstance::SaveGameData(int32 SaveNumber)
{
	//游戏存储
	if (ARuleOfTheGameState *InGameState = GetGameState())
	{
		
		if (FSaveSlot *InSlot = InGameState->GetSaveSlot(SaveNumber))
		{
			InSlot->DateText = FText::FromString(FDateTime::Now().ToString());
			InSlot->LevelName = LOCTEXT("LevelName", "TestMap");
			InSlot->ChapterName = LOCTEXT("ChapterName", "Hello World~~");

			InGameState->SaveGameData(SaveNumber);
		}
	}
	return false;
}

bool UTowersDefenceGameInstance::ClearGameData(int32 SaveNumber)
{
	if (ARuleOfTheGameState *InGameState = GetGameState())
	{
		return InGameState->ClearGameData(SaveNumber);
	}
	return false;
}

bool UTowersDefenceGameInstance::ReadGameData(int32 SaveNumber)
{
	return false;
}

bool UTowersDefenceGameInstance::IsSlotValid(int32 SaveNumber) const
{
	if (ARuleOfTheGameState *InGameState = GetGameState())
	{
		if (FSaveSlot *InSlot = InGameState->GetSaveSlot(SaveNumber))
		{
			return InSlot->bSave;
		}
	}

	return false;
}

FSaveSlotList * UTowersDefenceGameInstance::GetSlotList()
{
	if (ARuleOfTheGameState *InGameState = GetGameState())
	{
		return &InGameState->GetSaveSlotList();
	}

	return nullptr;
}

bool UTowersDefenceGameInstance::OpenLevel(int32 SaveNumber)
{
	if (FSaveSlot *InSlot = GetSaveSlot(SaveNumber))
	{
		if (InSlot->bSave)
		{
			//存储我们的存档是第几个
			SaveSlotNumber = SaveNumber;
			GameSaveType = EGameSaveType::ARCHIVES;
			OpenLevelOnServer(InSlot->LevelName);
			return true;
		}
	}

	return false;
}

UWorld * UTowersDefenceGameInstance::GetSimpleWorld() const
{
	return GetWorld();
}

FSaveSlot * UTowersDefenceGameInstance::GetSaveSlot(int32 SaveNumber)
{
	if (ARuleOfTheGameState *InGameState = GetGameState())
	{
		return InGameState->GetSaveSlot(SaveNumber);
	}

	return nullptr;
}

void UTowersDefenceGameInstance::Init()
{
	Super::Init();

	FSimpleScreenLoadingModule &SimpleScreenLoadingModule = FModuleManager::LoadModuleChecked<FSimpleScreenLoadingModule>("SimpleScreenLoading");
	SimpleScreenLoadingModule.SetupScreenLoading();
}

ARuleOfTheGameState * UTowersDefenceGameInstance::GetGameState() const
{
	return GetSafeWorld() == nullptr ? nullptr : GetSafeWorld()->GetGameState<ARuleOfTheGameState>();
}

UWorld* UTowersDefenceGameInstance::GetSafeWorld() const
{
	if (!GetWorld())
	{
		return GEngine->GetWorld();
	}

	return GetWorld();
}

void UTowersDefenceGameInstance::OpenLevelOnServer(const FText &MapName)
{
	UGameplayStatics::OpenLevel(GetSafeWorld(), *MapName.ToString());
}

#undef LOCTEXT_NAMESPACE