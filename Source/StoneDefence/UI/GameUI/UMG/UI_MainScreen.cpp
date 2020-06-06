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
#include "Components/SizeBox.h"
#include "../../../Global/UI_Data.h"
#include "UI_RucksackSystem.h"
#include "UI_PlayerSkillSystem.h"
#include "UI_GameMenuSystem.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "../../../StoneDefenceUtils.h"
#include "UI_ArchivesSystem.h"
#include "SimplePopupType.h"
#include "SimplePopupUtils.h"

void UUI_MainScreen::NativeConstruct()
{
	Super::NativeConstruct();

	SettingsButton->OnClicked.AddDynamic(this, &UUI_MainScreen::Settings);

	{
		FOnButtonClickedEvent Delegate;
		Delegate.AddDynamic(this, &UUI_MainScreen::SaveGame);
		GameMenuSystem->BindSaveGame(Delegate);
	}
	{
		FOnButtonClickedEvent Delegate;
		Delegate.AddDynamic(this, &UUI_MainScreen::SaveSettings);
		GameMenuSystem->BindSaveSettings(Delegate);
	}
	{
		FOnButtonClickedEvent Delegate;
		Delegate.AddDynamic(this, &UUI_MainScreen::ReturnGame);
		GameMenuSystem->BindReturnGame(Delegate);
	}
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

void UUI_MainScreen::UpdatePlayerSkillSlot(const FGuid &PlayerSKillSlotGUID, bool bInCD)
{
	if (PlayerSkillSystem)
	{
		PlayerSkillSystem->UpdatePlayerSkillSlot(PlayerSKillSlotGUID, bInCD);
	}
}

void UUI_MainScreen::Settings()
{
	if (GameMenuSystem->GetVisibility() == ESlateVisibility::Hidden)
	{
		NewWindows->SetVisibility(ESlateVisibility::Visible);
		GameMenuSystem->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		NewWindows->SetVisibility(ESlateVisibility::Hidden);
		GameMenuSystem->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUI_MainScreen::SaveGame()
{
 	if (UUI_ArchivesSystem *ArchivesSystem = StoneDefenceUtils::CreateAssistWidget<UUI_MainScreen, UUI_ArchivesSystem>(this, ArchivesSystemClass, BoxList))
 	{
 		ArchivesSystem->BindWindows(
 			[&](FSimpleDelegate InDelegate)
 		{
 			SimplePopupUtils::CreatePopup(
 				GetWorld(),
 				PopupClass,
 				NSLOCTEXT("UUI_MainScreen", "DeleteSaveSlot", "Are you sure you want to delete this archive ?"),
 				ESimplePopupType::TWO,
 				10.f,
 				InDelegate);
 		});
 	}
}

void UUI_MainScreen::SaveSettings()
{
	StoneDefenceUtils::CreateAssistWidget<UUI_MainScreen, UUI_GameSettingsSystem>(this, GameSettingsClass, BoxList);
}

void UUI_MainScreen::ReturnGame()
{
	Settings();
}