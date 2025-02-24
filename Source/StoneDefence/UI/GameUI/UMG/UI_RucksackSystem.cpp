// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_RucksackSystem.h"
#include "Inventory/UI_Inventory.h"

void UUI_RucksackSystem::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_RucksackSystem::UpdateInventorySlot(const FGuid &InventorySlotGUID, bool bInCD)
{
	if (Inventory)
	{
		Inventory->UpdateInventorySlot(InventorySlotGUID, bInCD);
	}
}
