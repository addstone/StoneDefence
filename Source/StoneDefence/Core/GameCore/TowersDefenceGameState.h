// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RuleOfTheGameState.h"
#include "../../Data/CharacterData.h"
#include "../../Data/Save/GameSaveData.h"
#include "../../StoneDefenceType.h"
#include "TowersDefenceGameState.generated.h"



extern FCharacterData CharacterDataNULL;
extern FBuildingTower BuildingTowerNULL;
class ARuleOfTheCharacter;
class AMonsters;
class ATowers;
class UGameSaveData;
class UGameSaveSlotList;
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

	virtual void BeginPlay() override;
public:
	ATowersDefenceGameState();
	UFUNCTION(BlueprintCallable, Category = Sapwn)
		AMonsters *SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator);
	
	UFUNCTION(BlueprintCallable, Category = Sapwn)
		ATowers *SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator);
	
	UFUNCTION(BlueprintCallable, Category = SaveData)
		bool SaveGameData(int32 SaveNumber);

	UFUNCTION(BlueprintCallable, Category = SaveData)
		bool ReadGameData(int32 SaveNumber);
protected:
	ARuleOfTheCharacter *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator);

	template<class T>
	T *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator)
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotator));
	}

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
};
