// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RuleOfThePlayerState.h"
#include "../../Data/Save/PlayerSaveData.h"
#include "../../Data/PlayerData.h"
#include "../../Data/BuildingTowerData.h"
#include "TowersDefencePlayerState.generated.h"




/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefencePlayerState : public ARuleOfThePlayerState
{
	GENERATED_BODY()
	
public:
	ATowersDefencePlayerState();

	FPlayerData &GetPlayerData();
	FBuildingTower &GetBuildingTower(const FGuid &ID);
	const TArray<const FGuid*> GetBuildingTowersID();
	const FBuildingTower &AddBuildingTower(const FGuid &ID, const FBuildingTower &Data);
	void RequestInventorySlotSwap(const FGuid &A, const FGuid &B);
	FBuildingTower &GetBuildingDataNULL();
	UPlayerSaveData *GetSaveData();
protected:
	UPROPERTY()
		UPlayerSaveData *SaveData;
private:

	UPROPERTY()
		FBuildingTower BuildingTowerNULL;
};
