// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RuleOfTheGameState.h"
#include "../../Data/CharacterData.h"
#include "TowersDefenceGameState.generated.h"


/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefenceGameState : public ARuleOfTheGameState
{
	GENERATED_BODY()
	
public:
	const FCharacterData &AddCharacterData(const FString &Hash, const FCharacterData &Data);
	bool RemoveCharacterData(const FString &Hash);
	FCharacterData GetCharacterData(const FString &Hash);


private:
	UPROPERTY()
		//TArray<FCharacterData*> CharacterDatas;
		TMap<FString, FCharacterData> CharacterDatas;
};
