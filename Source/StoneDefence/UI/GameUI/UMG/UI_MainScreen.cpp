// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MainScreen.h"
#include "Inventory/UI_InventorySlot.h"
#include "../../../DragDrop/StoneDefenceDragDropOperation.h"
#include "../../../Character/Core/RuleOfTheCharacter.h"
#include "../../Core/UI_RuleOfTheWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Tip/UI_TowerTip.h"
#include "Components/Image.h"
#include "../../../Global/UI_Data.h"
#include "UI_RucksackSystem.h"

void UUI_MainScreen::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_MainScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//显示角色信息
	if (ARuleOfTheCharacter *InCharacter = Cast<ARuleOfTheCharacter>(GetPlayerController()->GetHitResult().GetActor()))
	{
		const FCharacterData &CharacterData = GetGameState()->GetCharacterData(InCharacter->GUID);
		
			if (CharacterData.IsValid())
			{
				CharacterTip->InitTip(CharacterData);
				CharacterTip->SetVisibility(ESlateVisibility::HitTestInvisible);
				if (UCanvasPanelSlot* NewPanelSlot = Cast<UCanvasPanelSlot>(CharacterTip->Slot))
				{
					FVector2D ScrrenLocation = FVector2D::ZeroVector;
					UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetPlayerController(), GetPlayerController()->GetHitResult().Location, ScrrenLocation);
					NewPanelSlot->SetPosition(ScrrenLocation);
				}
				else
				{
					CharacterTip->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			else
			{
				CharacterTip->SetVisibility(ESlateVisibility::Hidden);
			}
		
	}
	else
	{
		CharacterTip->SetVisibility(ESlateVisibility::Hidden);
	}

	//显示集火对象
	if (ClickedTargetMonster &&  ClickedTargetMonster->IsActive())
	{
		if (UCanvasPanelSlot* NewPanelSlot = Cast<UCanvasPanelSlot>(FireConcentrationPoint->Slot))
		{
			FVector2D ScrrenLocation = FVector2D::ZeroVector;
			UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetPlayerController(), ClickedTargetMonster->GetActorLocation(), ScrrenLocation);
			NewPanelSlot->SetPosition(ScrrenLocation);
			FireConcentrationPoint->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
	else
	{
		ClickedTargetMonster = nullptr;
		FireConcentrationPoint->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUI_MainScreen::UpdateInventorySlot(const FGuid &InventorySlotGUID, bool bInCD)
{
	if (RucksackSystem)
	{
		RucksackSystem->UpdateInventorySlot(InventorySlotGUID, bInCD);
	}
}

