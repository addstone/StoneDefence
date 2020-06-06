// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSaveData.h"
#include "../../Core/GameCore/TowersDefencePlayerState.h"
#include "../PlayerSkillData.h"
#include "../../StoneDefenceUtils.h"
#include "../../Core/GameCore/TowersDefencePlayerController.h"
#include "../../Core/GameCore/TowersDefenceGameState.h"

void UPlayerSaveData::InitSaveGame(UWorld *InWorld)
{
	//if (ATowersDefenceGameState *InGameState = InWorld->GetGameState<ATowersDefenceGameState>())
	//{
	//	const TArray<FCharacterData*> &Datas = InGameState->GetTowerDataFromTable();

	//	//物品栏的塔slot 
	//	for (int32 i = 0; i < 21; i++)
	//	{
	//		FBuildingTower BuildingTower;
	//		if (Datas.IsValidIndex(i))
	//		{
	//			BuildingTower.TowerID = Datas[i]->ID;
	//			BuildingTower.NeedGold = Datas[i]->Glod;
	//			BuildingTower.MaxConstructionTowersCD = Datas[i]->CD;
	//			BuildingTower.ICO = Datas[i]->Icon.LoadSynchronous();
	//		}

	//		BuildingTowers.Add(FGuid::NewGuid(), BuildingTower);
	//	}

	//	//技能赋值 发生在服务器
	//	for (int32 i = 0; i < 10; i++)
	//	{
	//		FGuid ID = FGuid::NewGuid();
	//		if (PlayerData.SkillIDs.IsValidIndex(i))
	//		{
	//			AddPlayerSkill(InWorld, &ID, PlayerData.SkillIDs[i]);
	//		}
	//		else
	//		{
	//			PlayerSkillDatas.Add(ID, FPlayerSkillData());
	//		}
	//	}
	//}

	//物品栏的塔slot
	for (int32 i = 0; i < 21; i++)
	{
		BuildingTowers.Add(FGuid::NewGuid(), FBuildingTower());
	}

	for (int32 i = 0; i < 10; i++)
	{
		PlayerSkillDatas.Add(FGuid::NewGuid(), FPlayerSkillData());
	}
}

void UPlayerSaveData::AddPlayerSkill(UWorld *InWorld, const FGuid *Guid, int32 SkillID)
{
	if (ATowersDefencePlayerState *InPlayerState = InWorld->GetFirstPlayerController()->GetPlayerState<ATowersDefencePlayerState>())
	{
		if (const FPlayerSkillData *FSkill = InPlayerState->GetPlayerSkillDataFromTable(SkillID))
		{
			if (PlayerSkillDatas.Contains(*Guid))
			{
				PlayerSkillDatas[*Guid] = *FSkill;
			}
			else
			{
				PlayerSkillDatas.Add(*Guid, *FSkill);
			}

			//通知客户端更新添加的UI
			StoneDefenceUtils::CallUpdateAllClient(InWorld, [&](ATowersDefencePlayerController *MyPlayerController)
			{
				MyPlayerController->UpdatePlayerSkill_Client(*Guid, false);
			});
		}
	}
}
