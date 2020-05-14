// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceGameState.h"
#include "../../StoneDefenceMacro.h"
#include "../../Character/Core/RuleOfTheCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "../../Character/CharacterCore/Monsters.h"
#include "../../Character/CharacterCore/Towers.h"

FCharacterData CharacterDataNULL;


ATowersDefenceGameState::ATowersDefenceGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Towers(TEXT("/Game/GameData/TowersData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Monsters(TEXT("/Game/GameData/MonstersData"));
	AITowerCharacterData = MyTable_Towers.Object;
	AIMonsterCharacterData = MyTable_Monsters.Object;
}

AMonsters * ATowersDefenceGameState::SpawnMonster(int32 CharacterID, int32 CharacterLevel, FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<AMonsters>(CharacterID, CharacterLevel, AIMonsterCharacterData, Location, Rotator);
}

ATowers * ATowersDefenceGameState::SpawnTower(int32 CharacterID, int32 CharacterLevel, FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, AITowerCharacterData, Location, Rotator);
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
		;
		if (FCharacterData *CharacterData = GetCharacterData(CharacterID))
		{	
			//https://blog.csdn.net/qq_29523119/article/details/84455486
			UClass *NewClass = CharacterData->CharacterBlueprintKey.LoadSynchronous();
			if (GetWorld() && NewClass)
			{
				if (ARuleOfTheCharacter *RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotator))
				{
					RuleOfTheCharacter->GUID = FGuid::NewGuid();

					AddCharacterData(RuleOfTheCharacter->GUID, *CharacterData);
				}
			}
		}
	}

	return nullptr;
}

const FCharacterData & ATowersDefenceGameState::AddCharacterData(const FGuid &Hash, const FCharacterData &Data)
{
	return CharacterDatas.Add(Hash, Data);
}

bool ATowersDefenceGameState::RemoveCharacterData(const FGuid &Hash)
{
	return CharacterDatas.Remove(Hash);
}

FCharacterData & ATowersDefenceGameState::GetCharacterData(const FGuid &Hash)
{
	if (CharacterDatas.Contains(Hash))
	{
		return CharacterDatas[Hash];
	}
	
	SD_print_r(Error, "The current [%s] is invalid", *Hash.ToString());
	return CharacterDataNULL;
}
