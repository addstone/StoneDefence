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

	if (GetBuildingTower().TowersConstructionNumber > 0)
	{
		TCOCNumber->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	if (GetBuildingTower().TowersPerpareBuildingNumber > 0)
	{
		TPBNumber->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

FBuildingTower & UUI_InventorySlot::GetBuildingTower()
{
	return GetPlayerState()->GetBuildingTower(GUID);
}

void UUI_InventorySlot::ClearSlot()
{
	TowersIcon->SetVisibility(ESlateVisibility::Hidden);
	TowersCD->SetVisibility(ESlateVisibility::Hidden);
	TPBNumber->SetVisibility(ESlateVisibility::Hidden);
	TowersCDValue->SetVisibility(ESlateVisibility::Hidden);
	TCOCNumber->SetVisibility(ESlateVisibility::Hidden);
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

				GetBuildingTower().bDragICO = true;

				ClearSlot();
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
			MyInventorySlot->GetBuildingTower().bDragICO = false;
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
