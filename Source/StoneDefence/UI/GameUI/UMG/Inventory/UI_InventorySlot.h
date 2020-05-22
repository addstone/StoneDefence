// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Slot.h"
#include "UI_InventorySlot.generated.h"


class UImage;
class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_InventorySlot : public UUI_Slot
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
		UImage *TowersIcon;

	UPROPERTY(meta = (BindWidget))
		UImage *TowersCD;

	//Towers Prepare Building Number
	UPROPERTY(meta = (BindWidget))
		UTextBlock *TPBNumber;

	//Towers Completion Of Construction Number
	UPROPERTY(meta = (BindWidget))
		UTextBlock *TCOCNumber;

	UPROPERTY(meta = (BindWidget))
		UTextBlock *TowersCDValue;
	
	//Towers Inventory Slot Button
	UPROPERTY(meta = (BindWidget))
		UButton *TISButton;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnClickedWidget();

	void UpdateUI();

	FBuildingTower &GetBuildingTower();


};
