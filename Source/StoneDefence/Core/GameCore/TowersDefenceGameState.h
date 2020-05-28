// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RuleOfTheGameState.h"
#include "../../Data/CharacterData.h"
#include "../../Data/Save/GameSaveData.h"
#include "../../StoneDefenceType.h"
#include "TowersDefenceGameState.generated.h"



//extern FCharacterData CharacterDataNULL;
//extern FBuildingTower BuildingTowerNULL;
class ARuleOfTheCharacter;
class AMonsters;
class ATowers;
class UGameSaveData;
class UGameSaveSlotList;
struct FPlayerData;
struct FGameInstanceDatas;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefenceGameState : public ARuleOfTheGameState
{
	GENERATED_BODY()

	friend class AStoneDefenceGameMode;
	//塔数据
	UPROPERTY()
		UDataTable* AITowerCharacterData;

	//怪物数据
	UPROPERTY()
		UDataTable* AIMonsterCharacterData;


public:
	ATowersDefenceGameState();

	UFUNCTION(BlueprintCallable, Category = SaveData)
		bool SaveGameData(int32 SaveNumber);

	UFUNCTION(BlueprintCallable, Category = SaveData)
		bool ReadGameData(int32 SaveNumber);
protected:


public:

	const FCharacterData &AddCharacterData(const FGuid &ID, const FCharacterData &Data);
	const FBuildingTower &AddBuildingTower(const FGuid &ID, const FBuildingTower &Data);
	bool RemoveCharacterData(const FGuid &ID);
	FCharacterData &GetCharacterData(const FGuid &ID);
	FBuildingTower &GetBuildingTower(const FGuid &ID);
	const TArray<const FGuid*> GetBuildingTowersID();
	bool GetTowerDataFromTable(TArray<const FCharacterData*> &Datas);
	bool GetMonsterDataFromTable(TArray<const FCharacterData*> &Datas);
	const FCharacterData &GetCharacterDataByID(int32 ID, ECharacterType Type = ECharacterType::TOWER);
	void RequestInventorySlotSwap(const FGuid &A, const FGuid &B);

	FPlayerData &GetPlayerData();
	FGameInstanceDatas &GetGameData();

	FCharacterData &GetCharacterDataNULL();
	FBuildingTower &GetBuildingDataNULL();
protected:
	UGameSaveData *GetSaveData();
	UGameSaveSlotList *GetGameSaveSlotList();


private:
	UPROPERTY()
		UGameSaveData *SaveData;

	UPROPERTY()
		UGameSaveSlotList *SlotList;


	TArray<const FCharacterData*> CacheTowerDatas;

	TArray<const FCharacterData*> CacheMonsterDatas;

	FCharacterData CharacterDataNULL;
	FBuildingTower BuildingTowerNULL;
};
