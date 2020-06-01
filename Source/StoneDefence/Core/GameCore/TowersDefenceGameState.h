// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RuleOfTheGameState.h"
#include "../../Data/CharacterData.h"
#include "../../Data/Save/GameSaveData.h"
#include "../../StoneDefenceType.h"
#include "../../Data/BuildingTowerData.h"
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

	//角色的技能
	UPROPERTY()
		UDataTable* SkillCharacterData;

public:
	ATowersDefenceGameState();

	UFUNCTION(BlueprintCallable, Category = SaveData)
		bool SaveGameData(int32 SaveNumber);

	UFUNCTION(BlueprintCallable, Category = SaveData)
		bool ReadGameData(int32 SaveNumber);
protected:


public:

	FCharacterData &AddCharacterData(const FGuid &ID, const FCharacterData &Data);

	bool RemoveCharacterData(const FGuid &ID);
	FCharacterData &GetCharacterData(const FGuid &ID);
	const TArray<FCharacterData*> &GetTowerDataFromTable();
	const TArray<FCharacterData*> &GetMonsterDataFromTable();
	const FCharacterData &GetCharacterDataByID(int32 ID, ECharacterType Type = ECharacterType::TOWER);
	FGameInstanceDatas &GetGameData();
	FCharacterData &GetCharacterDataNULL();

	//模板技能
	const TArray<FSkillData*> &GetSkillDataFromTable();

	//动态技能的操作
	FSkillData &AddSkillData(const FGuid &CharacterID, const FGuid &SkillID, const FSkillData &Data);
	FSkillData &GetSkillData(const FGuid &SkillID);
	FSkillData &GetSkillData(const FGuid &CharacterID, const FGuid &SkillID);
	const FSkillData *GetSkillData(const int32 &SkillID);
	int32 RemoveSkillData(const FGuid &SkillID);

	UFUNCTION(/*Server*/)
		void AddSkillDataTemplateToCharacterData(const FGuid &CharacterID, int32 SkillID);

	bool IsVerificationSkillTemplate(const FGuid &CharacterID, int32 SkillID);
	bool IsVerificationSkillTemplate(const FCharacterData &CharacterData, int32 SkillID);
	//bool IsVerificationSkill(const FCharacterData &CharacterSkill, int32 SkillID);
	//bool IsVerificationSkill(const FGuid &CharacterID, int32 SkillID);

protected:
	UGameSaveData *GetSaveData();
	UGameSaveSlotList *GetGameSaveSlotList();


private:
	UPROPERTY()
		UGameSaveData *SaveData;

	UPROPERTY()
		UGameSaveSlotList *SlotList;


	TArray<FCharacterData*> CacheTowerDatas;
	TArray<FCharacterData*> CacheMonsterDatas;
	TArray<FSkillData*> CacheSkillDatas;

	FCharacterData CharacterDataNULL;
	FSkillData SkillDataNULL;
};
