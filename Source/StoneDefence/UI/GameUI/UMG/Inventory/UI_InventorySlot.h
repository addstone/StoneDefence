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

	UPROPERTY(EditDefaultsOnly, Category = UI)
		FName TowersMatCDName;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		FName TowersClearValueName;

	//CD��̬����
	UPROPERTY()
		class UMaterialInstanceDynamic* CDMaterialDynamic;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_ICODragDrog> ICODragDrogClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_TowerTip> TowerTipClass;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION()
		void OnClickedWidget();

	void UpdateUI();

	FBuildingTower &GetBuildingTower();

	void ClearSlot();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Tip)
		UWidget *GetTowerTip();

	void UpdateTowersCD(float InDeltaTime);
	void DrawTowersCD(float TowerCD);
	void DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber);
	void UpdateTowersBuildingInfo();

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
};
