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

FCharacterData CharacterDataNULL;


void ATowersDefenceGameState::BeginPlay()
{
	Super::BeginPlay();

	//if (1)
	//{
	//	SaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	//}
}

ATowersDefenceGameState::ATowersDefenceGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Towers(TEXT("/Game/GameData/TowersData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Monsters(TEXT("/Game/GameData/MonstersData"));
	AITowerCharacterData = MyTable_Towers.Object;
	AIMonsterCharacterData = MyTable_Monsters.Object;
}

AMonsters * ATowersDefenceGameState::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<AMonsters>(CharacterID, CharacterLevel, AIMonsterCharacterData, Location, Rotator);
}

ATowers * ATowersDefenceGameState::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, AITowerCharacterData, Location, Rotator);
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

ARuleOfTheCharacter *ATowersDefenceGameState::SpawnCharacter(
	int32 CharacterID, 
	int32 CharacterLevel,
	UDataTable *InCharacterData, 
	const FVector &Location, 
	const FRotator &Rotator)
{
	if (InCharacterData)
	{
		TArray<FCharacterData*> Datas;
		InCharacterData->GetAllRows(TEXT("CharacterData"), Datas);
		auto GetCharacterData = [&](int32 ID) ->FCharacterData*
		{
			for (auto &Tmp : Datas)
			{
				if (Tmp->ID == ID)
				{
					return Tmp;
				}
			}
			return nullptr;
		};

		if (FCharacterData *CharacterData = GetCharacterData(CharacterID))
		{	
			//https://blog.csdn.net/qq_29523119/article/details/84455486
			UClass *NewClass = CharacterData->CharacterBlueprintKey.LoadSynchronous();
			if (GetWorld() && NewClass)
			{
				if (ARuleOfTheCharacter *RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotator))
				{
					//RuleOfTheCharacter->GetUniqueID();
					//RuleOfTheCharacter->GUID = FGuid::NewGuid();
					CharacterData->UpdateHealth();
					AddCharacterData(RuleOfTheCharacter->GUID, *CharacterData);
				}
			}
		}
	}

	return nullptr;
}

const FCharacterData & ATowersDefenceGameState::AddCharacterData(const FGuid &ID, const FCharacterData &Data)
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
	
	SD_print_r(Error, "The current [%i] is invalid", *ID.ToString());
	return CharacterDataNULL;
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
