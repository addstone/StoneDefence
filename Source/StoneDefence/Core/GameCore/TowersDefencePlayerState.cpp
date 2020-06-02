// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefencePlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "../../Data/Save/PlayerSaveData.h"
#include "../../StoneDefenceMacro.h"

ATowersDefencePlayerState::ATowersDefencePlayerState()
{
	//物品栏的塔slot
	for (int32 i = 0; i < 21; i++)
	{
		GetSaveData()->BuildingTowers.Add(FGuid::NewGuid(), FBuildingTower());
	}

	for (int32 i = 0; i < 10; i++)
	{
		GetSaveData()->PlayerSkillDatas.Add(FGuid::NewGuid(), FPlayerSkillData());
	}
}

FPlayerData & ATowersDefencePlayerState::GetPlayerData()
{
	return GetSaveData()->PlayerData;
}

FBuildingTower & ATowersDefencePlayerState::GetBuildingTower(const FGuid &ID)
{
	if (GetSaveData()->BuildingTowers.Contains(ID))
	{
		return GetSaveData()->BuildingTowers[ID];
	}

	SD_print(Error, "The current [%i] is invalid", *ID.ToString());
	return BuildingTowerNULL;
}

const TArray<const FGuid*> ATowersDefencePlayerState::GetBuildingTowersID()
{
	TArray<const FGuid*> TowersID;
	for (const auto &Tmp : GetSaveData()->BuildingTowers)
	{
		TowersID.Add(&Tmp.Key);
	}
	return TowersID;
}

const FBuildingTower & ATowersDefencePlayerState::AddBuildingTower(const FGuid &ID, const FBuildingTower &Data)
{
	return GetSaveData()->BuildingTowers.Add(ID, Data);
}

void ATowersDefencePlayerState::RequestInventorySlotSwap(const FGuid &A, const FGuid &B)
{
	FBuildingTower &ASlot = GetBuildingTower(A);
	FBuildingTower &BSlot = GetBuildingTower(B);

	if (ASlot.IsValid()) //交换
	{
		FBuildingTower TmpSlot = ASlot;
		ASlot = BSlot;
		BSlot = TmpSlot;
	}
	else //移动
	{
		ASlot = BSlot;
		BSlot.Init();
	}
}

FBuildingTower & ATowersDefencePlayerState::GetBuildingDataNULL()
{
	return BuildingTowerNULL;
}

UPlayerSaveData * ATowersDefencePlayerState::GetSaveData()
{
	if (!SaveData)
	{
		SaveData = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));
	}
	return SaveData;
}

FPlayerSkillData * ATowersDefencePlayerState::GetSkillDatas(const FGuid &SkillGuid)
{
	if (GetSaveData()->PlayerSkillDatas.Contains(SkillGuid))
	{
		return &GetSaveData()->PlayerSkillDatas[SkillGuid];
	}

	SD_print(Error, "The current [%s] is invalid", *SkillGuid.ToString());
	return nullptr;
}

const TArray<const FGuid*> ATowersDefencePlayerState::GetSkillDatasID()
{
	TArray<const FGuid*> SkillIDs;
	for (const auto &Tmp : GetSaveData()->PlayerSkillDatas)
	{
		SkillIDs.Add(&Tmp.Key);
	}

	return SkillIDs;
}

void ATowersDefencePlayerState::TowersPerpareBuildingNumber(const FGuid &InventoryGUID)
{
	FBuildingTower &BT = GetBuildingTower(InventoryGUID);
	if (BT.IsValid()) //服务器验证 防止作弊
	{
		if (BT.NeedGold <= GetPlayerData().GameGold)
		{
			BT.TowersPerpareBuildingNumber++;
			GetPlayerData().GameGold -= BT.NeedGold;

			if (BT.CurrentConstrictionTowersCD <= 0)
			{
				BT.ResetCD();
			}
		}
	}
}

void ATowersDefencePlayerState::SetTowersDragICOState(const FGuid &InventoryGUID, bool bDragICO)
{
	FBuildingTower &BT = GetBuildingTower(InventoryGUID);
	BT.bDragICO = bDragICO;
}

void ATowersDefencePlayerState::TowersConstructionNumber(const FGuid &InventoryGUID, int32 InValue /*= INDEX_NONE*/)
{
	FBuildingTower &BT = GetBuildingTower(InventoryGUID);
	if (BT.IsValid()) //服务器验证 防止作弊
	{
		BT.TowersConstructionNumber += InValue;
	}
}
