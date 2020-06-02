// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InventorySlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/TextBlock.h"
#include "../../../../DragDrop/StoneDefenceDragDropOperation.h"
#include "DragDrop/UI_ICODragDrog.h"
#include "Blueprint/UserWidget.h"
#include "../Tip/UI_TowerTip.h"
#include "../../../../Data/CharacterData.h"
#include "../../../../Global/UI_Data.h"


void UUI_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_InventorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_InventorySlot::OnClickedWidget()
{
	if (GetBuildingTower().IsValid()) //客户端验证 降低网络带宽
	{
		//通知服务器对塔的数量进行增加
		GetPlayerState()->TowersPerpareBuildingNumber(GUID);
	}
}

void UUI_InventorySlot::UpdateUI()
{
	UpdateSlotUI(GetBuildingTower().ICO, GetBuildingTower().TowersConstructionNumber);

	UpdateTowersBuildingInfo();
}

FBuildingTower & UUI_InventorySlot::GetBuildingTower()
{
	return GetPlayerState()->GetBuildingTower(GUID);
}

void UUI_InventorySlot::ClearSlot()
{
	Super::ClearSlot();
	TPBNumber->SetVisibility(ESlateVisibility::Hidden);
}

UWidget * UUI_InventorySlot::GetTowerTip()
{
	if (TowerTipClass)
	{
		if (UUI_TowerTip *TowerTip = CreateWidget<UUI_TowerTip>(GetWorld(), TowerTipClass))
		{
			const FCharacterData &TowerDataInfo = GetGameState()->GetCharacterDataByID(GetBuildingTower().TowerID);
			if (TowerDataInfo.IsValid())
			{
				TowerTip->InitTip(TowerDataInfo);

				return TowerTip;
			}
		}
	}

	return nullptr;
}

void UUI_InventorySlot::UpdateTowersCD(float InDeltaTime)
{
	if (GetBuildingTower().CurrentConstrictionTowersCD > 0)
	{
		DrawSlotCD(GetBuildingTower().GetTowerConstructionTimePercentage());
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

		
		DrawSlotCD(0.0f);

		if (GetBuildingTower().TowersPerpareBuildingNumber > 0)
		{
			GetBuildingTower().ResetCD();
		}
		UpdateTowersBuildingInfo();
	}
}

void UUI_InventorySlot::UpdateTowersBuildingInfo()
{
	UpdateSloInfo(GetBuildingTower().TowersConstructionNumber, GetBuildingTower().CurrentConstrictionTowersCD);
	DisplayNumber(TPBNumber, GetBuildingTower().TowersPerpareBuildingNumber);
}

FReply UUI_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton || InMouseEvent.IsTouchEvent())
	{
		FReply Reply = FReply::Handled();
		TSharedPtr<SWidget> SlateWidgetDrag = GetCachedWidget();
		if (SlateWidgetDrag.IsValid())
		{
			Reply.DetectDrag(SlateWidgetDrag.ToSharedRef(), EKeys::RightMouseButton);
			return Reply;
		}
	}
	return FReply::Handled();
}

void UUI_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (GetBuildingTower().IsValid() && ICODragDrogClass)
	{
		if (UUI_ICODragDrog* ICODragDrog = CreateWidget<UUI_ICODragDrog>(GetWorld(), ICODragDrogClass))
		{
			if (UStoneDefenceDragDropOperation* StoneDefenceDragDropOperation = NewObject<UStoneDefenceDragDropOperation>(GetTransientPackage(), UStoneDefenceDragDropOperation::StaticClass()))
			{
				StoneDefenceDragDropOperation->SetFlags(RF_StrongRefOnFrame);
				ICODragDrog->DrawICON(GetBuildingTower().ICO);
				StoneDefenceDragDropOperation->DefaultDragVisual = ICODragDrog;
				StoneDefenceDragDropOperation->Payload = this;
				OutOperation = StoneDefenceDragDropOperation;

				//通知服务器 客户端要进行拖拽
				GetPlayerState()->SetTowersDragICOState(GUID, true);

				ClearSlot();//隐藏自己
			}
		}
	}

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UUI_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bool bDrop = false;

	if (UStoneDefenceDragDropOperation* StoneDefenceDragDropOperation = Cast<UStoneDefenceDragDropOperation>(InOperation))
	{
		if (UUI_InventorySlot* MyInventorySlot = Cast<UUI_InventorySlot>(StoneDefenceDragDropOperation->Payload))
		{
			//服务器请求
			GetPlayerState()->SetTowersDragICOState(MyInventorySlot->GUID, false);
			GetPlayerState()->RequestInventorySlotSwap(GUID, MyInventorySlot->GUID);

			UpdateUI();
			MyInventorySlot->UpdateUI();
			bDrop = true;
		}
	}

	return bDrop;
}

void UUI_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bLockGUID)
	{
		TowerICOGUID = GUID;
	}
}

void UUI_InventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{

}
