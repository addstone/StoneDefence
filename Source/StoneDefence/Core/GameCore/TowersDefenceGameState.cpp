// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceGameState.h"
#include "../../StoneDefenceMacro.h"
#include "../../Character/Core/RuleOfTheCharacter.h"

FCharacterData CharacterDataNULL;


ATowersDefenceGameState::ATowersDefenceGameState()
{

}

ARuleOfTheCharacter *ATowersDefenceGameState::SpawnCharacter(const FVector &Location, const FRotator &Rotator)
{
	if (GetWorld())
	{
		if (ARuleOfTheCharacter *RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(ARuleOfTheCharacter::StaticClass(), Location, Rotator))
		{
			RuleOfTheCharacter->GUID = FGuid::NewGuid();
			FCharacterData CharacterData;
			AddCharacterData(RuleOfTheCharacter->GUID, CharacterData);
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
