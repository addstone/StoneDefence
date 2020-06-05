// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interface/SimpleArchivesInterface.h"
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

	virtual bool ReadGameData(int32 SaveNumber);

	virtual class UWorld *GetSimpleWorld() const;

	virtual void Init() override;

	ARuleOfTheGameState *GetGameState() const;

	class UWorld* GetSafeWorld() const;
};
