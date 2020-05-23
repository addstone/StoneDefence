// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Slot.h"
#include "UI_Inventory.generated.h"


class UUniformGridPanel;
class UUI_InventorySlot;
class UMaterialInterface;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_Inventory : public UUI_Slot
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel *SlotArrayInventory;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUI_InventorySlot> InventorySlotClass;
	
protected:
	virtual void NativeConstruct() override;
	FBuildingTower &GetBuildingTower();
	void LayoutInventroySlot(int32 ColumNumber, int32 RowNumber);

	void SpawnTowersDollPressed();
	void SpawnTowersDollReleased();
private:
	TArray<UUI_InventorySlot*> InventorySlotArray;
};
