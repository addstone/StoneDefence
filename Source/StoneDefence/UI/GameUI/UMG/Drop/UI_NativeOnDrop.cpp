// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_NativeOnDrop.h"
#include "../../../../DragDrop/StoneDefenceDragDropOperation.h"
#include "../Inventory/UI_InventorySlot.h"

bool UUI_NativeOnDrop::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bool bDrop = false;

	if (UStoneDefenceDragDropOperation* StoneDefenceDragDropOperation = Cast<UStoneDefenceDragDropOperation>(InOperation))
	{
		if (UUI_InventorySlot* MyInventorySlot = Cast<UUI_InventorySlot>(StoneDefenceDragDropOperation->Payload))
		{
			MyInventorySlot->GetBuildingTower().bDragICO = false;

			MyInventorySlot->UpdateUI();
			bDrop = true;
		}
	}

	return bDrop;
}