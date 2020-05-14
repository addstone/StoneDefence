// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RuleOfTheGameState.h"
#include "../../Data/CharacterData.h"
#include "TowersDefenceGameState.generated.h"

extern FCharacterData CharacterDataNULL;
class ARuleOfTheCharacter;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefenceGameState : public ARuleOfTheGameState
{
	GENERATED_BODY()
	
public:
	ATowersDefenceGameState();

	ARuleOfTheCharacter *SpawnCharacter(const FVector &Location, const FRotator &Rotator);

	template<class T>
	T SpawnCharacter(const FVector &Location, const FRotator &Rotator)
	{
		return Cast<T>(SpawnCharacter(Location, Rotator));
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
