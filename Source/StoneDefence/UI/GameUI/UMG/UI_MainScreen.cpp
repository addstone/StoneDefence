// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MainScreen.h"
#include "Inventory/UI_InventorySlot.h"
#include "../../../DragDrop/StoneDefenceDragDropOperation.h"
#include "../../../Character/Core/RuleOfTheCharacter.h"
#include "../../Core/UI_RuleOfTheWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Tip/UI_TowerTip.h"

void UUI_MainScreen::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_MainScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

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
