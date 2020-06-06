// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interface/SimpleArchivesInterface.h"
#include "../../StoneDefenceType.h"
#include "TowersDefenceGameInstance.generated.h"



class ARuleOfTheGameState;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UTowersDefenceGameInstance : public UGameInstance, public ISimpleArchivesInterface
{
	GENERATED_BODY()
	
public:
	UTowersDefenceGameInstance();

	virtual int32 GetSaveSlotNumber() const;

	virtual	bool SaveGameData(int32 SaveNumber);

	virtual	bool ClearGameData(int32 SaveNumber);

	virtual bool ReadGameData(int32 SaveNumber);

	virtual	void SetSaveNumber(int32 SaveNumber);

	virtual bool IsSlotValid(int32 SaveNumber) const;

	virtual FSaveSlotList *GetSlotList();

	virtual bool OpenLevel(int32 SaveNumber);

	virtual class UWorld *GetSimpleWorld() const;

	virtual FSaveSlot *GetSaveSlot(int32 SaveNumber);

	virtual void Init() override;

	ARuleOfTheGameState *GetGameState() const;

	class UWorld* GetSafeWorld() const;

	int32 GetCurrentSaveSlotNumber() const;

	UFUNCTION(/*Server*/)
		void SetCurrentSaveSlotNumber(int32 InSaveSlotNumber);

	EGameSaveType GetGameType() { return GameSaveType; };

protected:
	UFUNCTION(/*Server*/)
		void OpenLevelOnServer(const FText &MapName);

protected:
	UPROPERTY()
		int32 SaveSlotNumber;

	//ÓÎÏ·´æ´¢×´Ì¬flag
	EGameSaveType GameSaveType;
};
