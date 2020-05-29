// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceGameState.h"
#include "../../StoneDefenceMacro.h"
#include "../../Character/Core/RuleOfTheCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "../../Character/CharacterCore/Monsters.h"
#include "../../Character/CharacterCore/Towers.h"
#include "../../Data/Save/GameSaveData.h"
#include "Kismet/GameplayStatics.h"
#include "../../Data/Save/GameSaveSlotList.h"
#include "Engine/StaticMeshActor.h"
#include "../../Data/CharacterData.h"
#include "../../Data/PlayerData.h"
#include "../../Data/GameData.h"
#include "../../Items/SpawnPoint.h"
#include "../../StoneDefenceUtils.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif


ATowersDefenceGameState::ATowersDefenceGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Towers(TEXT("/Game/GameData/TowersData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Monsters(TEXT("/Game/GameData/MonstersData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Skill(TEXT("/Game/GameData/CharacterSkillData"));

	AITowerCharacterData = MyTable_Towers.Object;
	AIMonsterCharacterData = MyTable_Monsters.Object;
	SkillCharacterData = MyTable_Skill.Object;


}

bool ATowersDefenceGameState::SaveGameData(int32 SaveNumber)
{
	if (SaveData && SlotList)
	{
		SlotList->SlotList.AddGameDataByNumber(SaveNumber);
		return UGameplayStatics::SaveGameToSlot(SlotList, FString::Printf(TEXT("SlotList")), 0)
			&&
			UGameplayStatics::SaveGameToSlot(SaveData, FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0);
	}
	return false;
}

bool ATowersDefenceGameState::ReadGameData(int32 SaveNumber)
{
	SaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0));

	return SaveData != NULL;
}

FCharacterData & ATowersDefenceGameState::AddCharacterData(const FGuid &ID, const FCharacterData &Data)
{
	return GetSaveData()->CharacterDatas.Add(ID, Data);
}

bool ATowersDefenceGameState::RemoveCharacterData(const FGuid &ID)
{
	return GetSaveData()->CharacterDatas.Remove(ID);
}

FCharacterData & ATowersDefenceGameState::GetCharacterData(const FGuid &ID)
{
	if (GetSaveData()->CharacterDatas.Contains(ID))
	{
		return GetSaveData()->CharacterDatas[ID];
	}
	
	SD_print(Error, "The current [%i] is invalid", *ID.ToString());
	return CharacterDataNULL;
}

const FCharacterData & ATowersDefenceGameState::GetCharacterDataByID(int32 ID, ECharacterType Type /*= ECharacterType::TOWER*/)
{
	auto GetMyCharacterData = [&](const TArray< FCharacterData*> &Datas, int32 ID)->const FCharacterData &
	{
		for (const auto &Tmp : Datas)
		{
			if (Tmp->ID == ID)
			{
				return *Tmp;
			}
		}
		return CharacterDataNULL;
	};

	switch (Type)
	{
	case ECharacterType::TOWER:
	{
		const TArray< FCharacterData*> &Datas = GetTowerDataFromTable();
		return GetMyCharacterData(Datas, ID);
	}
		
	case ECharacterType::MONSTER:
	{
		const TArray< FCharacterData*> &Datas = GetMonsterDataFromTable();

		return GetMyCharacterData(Datas, ID);
	}
	}
	return CharacterDataNULL;
}

const TArray<FCharacterData*> & ATowersDefenceGameState::GetTowerDataFromTable()
{
	if (!CacheTowerDatas.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("CharacterData"), CacheTowerDatas);
	}
	return CacheTowerDatas;
}

const TArray<FCharacterData*> & ATowersDefenceGameState::GetMonsterDataFromTable()
{
	if (!CacheMonsterDatas.Num())
	{
		AIMonsterCharacterData->GetAllRows(TEXT("CharacterData"), CacheMonsterDatas);
	}
	return CacheMonsterDatas;
}

FGameInstanceDatas & ATowersDefenceGameState::GetGameData()
{
	return GetSaveData()->GamerDatas;
}

FCharacterData & ATowersDefenceGameState::GetCharacterDataNULL()
{
	return CharacterDataNULL;
}

const TArray<FSkillData*> & ATowersDefenceGameState::GetSkillDataFromTable()
{
	if (!CacheSkillDatas.Num())
	{
		SkillCharacterData->GetAllRows(TEXT("Slill Data"), CacheSkillDatas);
	}

	return CacheSkillDatas;
}

FSkillData & ATowersDefenceGameState::AddSkillData(const FGuid &CharacterID, const FGuid &SkillID, const FSkillData &Data)
{
	FCharacterData &InCharacterData = GetCharacterData(CharacterID);
	
		if (InCharacterData.IsValid())
		{
			return InCharacterData.AdditionalSkillData.Add(SkillID, Data);
		}
	

	return SkillDataNULL;
}

FSkillData & ATowersDefenceGameState::GetSkillData(const FGuid &SkillID)
{
	for (auto &Tmp : GetSaveData()->CharacterDatas)
	{
		if (Tmp.Value.AdditionalSkillData.Contains(SkillID))
		{
			return Tmp.Value.AdditionalSkillData[SkillID];
		}
	}
	return SkillDataNULL;
}

FSkillData & ATowersDefenceGameState::GetSkillData(const FGuid &CharacterID, const FGuid &SkillID)
{
	FCharacterData &InCharacterData = GetCharacterData(CharacterID);
		if (InCharacterData.IsValid())
		{
			if (InCharacterData.AdditionalSkillData.Contains(SkillID))
			{
				return InCharacterData.AdditionalSkillData[SkillID];
			}
		}
	
	return SkillDataNULL;
}

int32 ATowersDefenceGameState::RemoveSkillData(const FGuid &SkillID)
{
	for (auto &Tmp : GetSaveData()->CharacterDatas)
	{
		return Tmp.Value.AdditionalSkillData.Remove(SkillID);
	}

	return INDEX_NONE;
}

void ATowersDefenceGameState::InitSkill(FCharacterData &InCharacterData)
{
	const TArray<FSkillData*> &InSkillData = GetSkillDataFromTable();
	for (auto &Tmp : InCharacterData.CharacterSkillID)
	{
		for (const FSkillData *NewSkill : InSkillData)
		{
			if (Tmp == NewSkill->ID)
			{
				InCharacterData.CharacterSkill.Add(*NewSkill);
				break;
			}
		}
	}
}

UGameSaveData * ATowersDefenceGameState::GetSaveData()
{
	if (!SaveData)
	{
		SaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	}
	return SaveData;
}

UGameSaveSlotList * ATowersDefenceGameState::GetGameSaveSlotList()
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





#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif