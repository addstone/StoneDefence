// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory.h"
#include "Components/UniformGridSlot.h"
#include "Components/UniformGridPanel.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "UI_InventorySlot.h"
#include "../../../Core/UI_RuleOfTheWidget.h"
#include "../../../../StoneDefenceUtils.h"
#include "../../../../Global/UI_Data.h"

void UUI_Inventory::UpdateInventorySlot(const FGuid &InventorySlotGUID, bool bInCD)
{
	for (auto &Tmp : InventorySlotArray)
	{
		if (Tmp->GUID == InventorySlotGUID)
		{
			if (bInCD)
			{
				Tmp->DrawSlotCD(Tmp->GetBuildingTower().GetTowerConstructionTimePercentage());
			}
			else
			{
				Tmp->DrawSlotCD(0.f);
			}

			Tmp->UpdateTowersBuildingInfo();
			break;
		}
	}
}

void UUI_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	LayoutInventroySlot(3, 7);

	GetPlayerController()->EventMouseMiddlePressed.BindUObject(this, &UUI_Inventory::SpawnTowersDollPressed);
	GetPlayerController()->EventFMouseMiddleReleased.BindUObject(this, &UUI_Inventory::SpawnTowersDollReleased);
}

FBuildingTower &UUI_Inventory::GetBuildingTower()
{
	return GetPlayerState()->GetBuildingTower(TowerICOGUID);
}
void UUI_Inventory::LayoutInventroySlot(int32 ColumNumber, int32 RowNumber)
{
	if (InventorySlotClass && GetPlayerState())
	{
		const TArray<const FGuid*> ID = GetPlayerState()->GetBuildingTowersID();
		for (int32 MyRow = 0; MyRow < RowNumber; MyRow++)
		{
			//排序物品栏
			for (int32 MyColum = 0; MyColum < ColumNumber; MyColum++)
			{
				if (UUI_InventorySlot *SlotWidget = CreateWidget<UUI_InventorySlot>(GetWorld(), InventorySlotClass))
				{
					if (UUniformGridSlot *GridSlot = SlotArrayInventory->AddChildToUniformGrid(SlotWidget))
					{
						GridSlot->SetColumn(MyColum);
						GridSlot->SetRow(MyRow);
						GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
					}
					InventorySlotArray.Add(SlotWidget);

					SlotWidget->GUID = *ID[MyRow * ColumNumber + MyColum];
					SlotWidget->UpdateUI();
				}
			}
		}
	}
}

void UUI_Inventory::SpawnTowersDollPressed()
{
	if (GetBuildingTower().IsValid())
	{
		bLockGUID = true;
		if (GetBuildingTower().TowersConstructionNumber >= 1)
		{
			int32 TowerID = GetBuildingTower().TowerID;
			if (AStaticMeshActor * MeshActor = StoneDefenceUtils::SpawnTowersDoll(GetWorld(), TowerID))
			{
				for (int32 i = 0; i < MeshActor->GetStaticMeshComponent()->GetNumMaterials(); i++)
				{
					MeshActor->GetStaticMeshComponent()->SetMaterial(i, DollMaterial);
				}
				TowerDoll = MeshActor;
			}
		}
	}
}

void UUI_Inventory::SpawnTowersDollReleased()
{
	if (GetBuildingTower().IsValid())
	{
		if (TowerDoll)
		{
			if (GetBuildingTower().TowersConstructionNumber >= 1)
			{
				if (/*AActor*/ATowers *CharacterActor = GetPlayerController()->SpawnTower(GetBuildingTower().TowerID, 1, TowerDoll->GetActorLocation(), TowerDoll->GetActorRotation()))
				{
					//GetBuildingTower().TowersConstructionNumber--;
					//通知服务器 更新构建塔的数量
					GetPlayerState()->TowersConstructionNumber(TowerICOGUID);

					//通知客户端更新
					CallInventorySlotBreak([&](UUI_InventorySlot* InInventorySlot)
					{
						if (InInventorySlot->GUID == TowerICOGUID)
						{
							InInventorySlot->UpdateTowersBuildingInfo();
							return true;
						}

						return false;
					});
				}
			}

			TowerDoll->Destroy();
			TowerDoll = nullptr;
		}
	}

	bLockGUID = false;
	TowerICOGUID = FGuid();
}

void UUI_Inventory::CallInventorySlotBreak(TFunction<bool(UUI_InventorySlot*)> InventorySlotLamada)
{
	for (auto &TmpSlot : InventorySlotArray)
	{
		if (InventorySlotLamada(TmpSlot))
		{
			break;
		}
	}
}
