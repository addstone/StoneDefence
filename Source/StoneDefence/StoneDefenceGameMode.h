// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StoneDefenceGameMode.generated.h"


class ARuleOfTheCharacter;
class AMonsters;
class ATowers;
class UDataTable;
class ATowersDefencePlayerController;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API AStoneDefenceGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AStoneDefenceGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = Sapwn)
		AMonsters *SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator);

	UFUNCTION(BlueprintCallable, Category = Sapwn)
		ATowers *SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator);



protected:
	void SpawnMonstersRule(float DeltaSeconds);
	void SpawnMainTowersRule();
	ARuleOfTheCharacter *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator);

	template<class T>
	T *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator)
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotator));
	}

	void UpdateSkill(float DeltaSeconds);


};
