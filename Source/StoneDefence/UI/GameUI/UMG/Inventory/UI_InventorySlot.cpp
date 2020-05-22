// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventorySlot.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UUI_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	TISButton->OnClicked.AddDynamic(this, &UUI_InventorySlot::OnClickedWidget);
}

void UUI_InventorySlot::OnClickedWidget()
{

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
