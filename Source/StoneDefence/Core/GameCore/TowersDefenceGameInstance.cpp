// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceGameInstance.h"
#include "Modules/ModuleManager.h"
#include "SimpleScreenLoading.h"
#include "../RuleOfTheGameState.h"
#include "Kismet/GameplayStatics.h"
#include "../../StoneDefenceUtils.h"
#include "../RuleOfThePlayerState.h"
#include "../../StoneDefenceMacro.h"

#define LOCTEXT_NAMESPACE "TowerGameInstance"

UTowersDefenceGameInstance::UTowersDefenceGameInstance()
	:ISimpleArchivesInterface()
	, SaveSlotNumber(INDEX_NONE)
	, GameSaveType(EGameSaveType::NONE)
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
	bool bSave = false;

	//游戏存储
	if (ARuleOfTheGameState *InGameState = GetGameState())
	{
		
		if (FSaveSlot *InSlot = InGameState->GetSaveSlot(SaveNumber))
		{
			InSlot->DateText = FText::FromString(FDateTime::Now().ToString());
			InSlot->LevelName = LOCTEXT("LevelName", "TestMap");
			InSlot->ChapterName = LOCTEXT("ChapterName", "Hello World~~");

			InSlot->GameThumbnail.ReleaseResources();
			InSlot->GameThumbnail.ScrPath = GAMETHUMBNAIL_SCREENSHOT(
				400, 200,
				InSlot->GameThumbnail.GameThumbnail,
				GetWorld())->GetFilename();

			bSave = InGameState->SaveGameData(SaveNumber);
		}
	}

	//玩家数据存储
	StoneDefenceUtils::CallUpdateAllBaseClient(GetSafeWorld(), [&](APlayerController *InPlayerController)
	{
		if (ARuleOfThePlayerState *InState = InPlayerController->GetPlayerState<ARuleOfThePlayerState>())
		{
			bSave = InState->SaveGameData(SaveNumber);
		}
	});

	return bSave;
}

bool UTowersDefenceGameInstance::ClearGameData(int32 SaveNumber)
{
	bool bSave = false;
	if (ARuleOfTheGameState *InGameState = GetGameState())
	{
		bSave = InGameState->ClearGameData(SaveNumber);
	}

	StoneDefenceUtils::CallUpdateAllBaseClient(GetSafeWorld(), [&](APlayerController *InPlayerController)
	{
		if (ARuleOfThePlayerState *InState = InPlayerController->GetPlayerState<ARuleOfThePlayerState>())
		{
			bSave = InState->ClearPlayerData(SaveNumber);
		}
	});

	return bSave;
}

bool UTowersDefenceGameInstance::ReadGameData(int32 SaveNumber)
{
	return false;
}

void UTowersDefenceGameInstance::SetSaveNumber(int32 SaveNumber)
{
	SetCurrentSaveSlotNumber(SaveNumber);
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

int32 UTowersDefenceGameInstance::GetCurrentSaveSlotNumber() const
{
	return SaveSlotNumber;
}

void UTowersDefenceGameInstance::ClearSaveMark()
{
	SaveSlotNumber = INDEX_NONE;
	GameSaveType = EGameSaveType::NONE;
}

void UTowersDefenceGameInstance::SetCurrentSaveSlotNumber(int32 InSaveSlotNumber)
{
	SaveSlotNumber = InSaveSlotNumber;
}

void UTowersDefenceGameInstance::OpenLevelOnServer(const FText &MapName)
{
	UGameplayStatics::OpenLevel(GetSafeWorld(), *MapName.ToString());
}

#undef LOCTEXT_NAMESPACE