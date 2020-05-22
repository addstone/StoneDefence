// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventorySlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/TextBlock.h"

void UUI_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	TISButton->OnClicked.AddDynamic(this, &UUI_InventorySlot::OnClickedWidget);

	if (TowersCD)
	{
		CDMaterialDynamic = TowersCD->GetDynamicMaterial();
	}
}

void UUI_InventorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!GetBuildingTower().bLockCD)
	{
		if (!GetBuildingTower().bDragICO)
		{
			UpdateTowersCD(InDeltaTime);

		}
	}
}

void UUI_InventorySlot::OnClickedWidget()
{
	if (GetBuildingTower().IsValid()) //客户端验证 降低网络带宽
	{
		//通知服务器对塔的数量进行增加
		GetBuildingTower().TowersPerpareBuildingNumber++;
		if (GetBuildingTower().CurrentConstrictionTowersCD <= 0)
		{
			GetBuildingTower().ResetCD();
		}
	}
}

void UUI_InventorySlot::UpdateUI()
{
	if (GetBuildingTower().ICO)
	{
		TowersIcon->SetBrushFromTexture(GetBuildingTower().ICO);
		TowersIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		TowersIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}

FBuildingTower & UUI_InventorySlot::GetBuildingTower()
{
	return GetGameState()->GetBuildingTower(GUID);
}

void UUI_InventorySlot::UpdateTowersCD(float InDeltaTime)
{
	if (GetBuildingTower().CurrentConstrictionTowersCD > 0)
	{
		DrawTowersCD(GetBuildingTower().GetTowerConstructionTimePercentage());
		GetBuildingTower().CurrentConstrictionTowersCD -= InDeltaTime;
		GetBuildingTower().bCallUpdateTowersInfo = true;
		UpdateTowersBuildingInfo();
	}
	else if(GetBuildingTower().bCallUpdateTowersInfo)
	{
		GetBuildingTower().bCallUpdateTowersInfo = false;
		//准备构建的塔
		GetBuildingTower().TowersPerpareBuildingNumber--;
		GetBuildingTower().TowersConstructionNumber++;

		
		DrawTowersCD(0.0f);

		if (GetBuildingTower().TowersPerpareBuildingNumber > 0)
		{
			GetBuildingTower().ResetCD();
		}
		UpdateTowersBuildingInfo();
	}
}

void UUI_InventorySlot::DrawTowersCD(float TowerCD)
{
	if (CDMaterialDynamic)
	{
		if (TowerCD > 0.0f && TowerCD < 1.0f)
		{
			CDMaterialDynamic->SetScalarParameterValue(TowersClearValueName, true);
			TowersCD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			CDMaterialDynamic->SetScalarParameterValue(TowersClearValueName, false);
			TowersCD->SetVisibility(ESlateVisibility::Hidden);
		}
		CDMaterialDynamic->SetScalarParameterValue(TowersMatCDName, TowerCD);
	}
}

void UUI_InventorySlot::DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber)
{
	if (TextNumber < 1 || !GetBuildingTower().IsValid())
	{
		TextNumberBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TextNumberBlock->SetText(FText::FromString(FString::Printf(TEXT("%02d"), TextNumber)));
		TextNumberBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UUI_InventorySlot::UpdateTowersBuildingInfo()
{
	DisplayNumber(TowersCDValue, GetBuildingTower().CurrentConstrictionTowersCD);
	DisplayNumber(TCOCNumber, GetBuildingTower().TowersConstructionNumber);
	DisplayNumber(TPBNumber, GetBuildingTower().TowersPerpareBuildingNumber);
}
