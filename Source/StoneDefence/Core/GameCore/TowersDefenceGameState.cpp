// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceGameState.h"
#include "../../StoneDefenceMacro.h"

const FCharacterData & ATowersDefenceGameState::AddCharacterData(const FString &Hash, const FCharacterData &Data)
{
	return CharacterDatas.Add(Hash, Data);
}

bool ATowersDefenceGameState::RemoveCharacterData(const FString &Hash)
{
	return CharacterDatas.Remove(Hash);
}

FCharacterData /*&*/ ATowersDefenceGameState::GetCharacterData(const FString &Hash)
{
	for (auto &Tmp : CharacterDatas)
	{
		if (Tmp.Key == Hash)
		{
			return Tmp.Value;
		}
	}
	SD_print(Error, "The current [%s] is invalid", *Hash);
	return FCharacterData();
}
