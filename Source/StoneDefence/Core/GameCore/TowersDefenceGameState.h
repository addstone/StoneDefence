// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RuleOfTheGameState.h"
#include "../../Data/CharacterData.h"
#include "TowersDefenceGameState.generated.h"

extern FCharacterData CharacterDataNULL;
class ARuleOfTheCharacter;
class AMonsters;
class ATowers;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefenceGameState : public ARuleOfTheGameState
{
	GENERATED_BODY()
	
	//塔数据
	UPROPERTY()
		UDataTable* AITowerCharacterData;

	//怪物数据
	UPROPERTY()
		UDataTable* AIMonsterCharacterData;

public:
	ATowersDefenceGameState();

	AMonsters *SpawnMonster(int32 CharacterID, int32 CharacterLevel, FVector &Location, const FRotator &Rotator);
	ATowers *SpawnTower(int32 CharacterID, int32 CharacterLevel, FVector &Location, const FRotator &Rotator);
protected:
	ARuleOfTheCharacter *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator);

	template<class T>
	T *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator)
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotator));
	}

public:
	const FCharacterData &AddCharacterData(const FGuid &Hash, const FCharacterData &Data);
	bool RemoveCharacterData(const FGuid &Hash);
	FCharacterData &GetCharacterData(const FGuid &Hash);


private:
	UPROPERTY()
		//TArray<FCharacterData*> CharacterDatas;
		TMap<FGuid, FCharacterData> CharacterDatas;
};
