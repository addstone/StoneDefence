// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MainScreen.h"
#include "Inventory/UI_InventorySlot.h"
#include "../../../DragDrop/StoneDefenceDragDropOperation.h"

void UUI_MainScreen::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UUI_MainScreen::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
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
