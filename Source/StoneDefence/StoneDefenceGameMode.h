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
		ATowers *SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator);

	UFUNCTION(BlueprintCallable, Category = Sapwn)
		AMonsters *SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator);

	ATowers *SpawnTower(int32 CharacterID, const FVector &Location, const FRotator &Rotator, const FGuid &InCharacterGuid);
	AMonsters *SpawnMonster(int32 CharacterID, const FVector &Location, const FRotator &Rotator, const FGuid &InCharacterGuid);

protected:

	void SpawnMainTowersRule();
	void InitDataFormArchives();
	void InitData();

	ARuleOfTheCharacter *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator, const FGuid &InCharacterGuid = FGuid());

	template<class T>
	T *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector &Location, const FRotator &Rotator, const FGuid &InCharacterGuid = FGuid())
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotator, InCharacterGuid));
	}


	void UpdateSkill(float DeltaSeconds);

	void UpdateMonstersRule(float DeltaSeconds);

	void UpdatePlayerData(float DeltaSeconds);

	void UpdateGameData(float DeltaSeconds);

	void UpdatePlayerSkill(float DeltaSeconds);

	void UpdateInventory(float DeltaSeconds);

};
