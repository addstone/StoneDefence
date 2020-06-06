// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_PlayerSkillSystem.h"
#include "Skill/UI_SkillSlot.h"
#include "GameFramework/InputSettings.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/HorizontalBox.h"

void UUI_PlayerSkillSystem::NativeConstruct()
{
	Super::NativeConstruct();

	//auto KeyMapping = GetDefault<UInputSettings>()->GetActionMappings().FindByPredicate(
	//	[&](FInputActionKeyMapping &EntryUI)
	//	{
	//		return EntryUI.ActionName == "FreezeSkill";
	//	}
	//);

	LayoutPlayerSkillSlot();
}

void UUI_PlayerSkillSystem::LayoutPlayerSkillSlot()
{
	if (SkillSlotClass)
	{
		const TArray<const FGuid *> PlayerSkillGUIDs = GetPlayerState()->GetSkillDatasID();
		for (int32 i = 0; i < PlayerSkillGUIDs.Num(); i++)
		{
			if (UUI_SkillSlot *SkillSlot = CreateWidget<UUI_SkillSlot>(GetWorld(), SkillSlotClass))
			{
				SkillSlot->GUID = *PlayerSkillGUIDs[i];
				if (UHorizontalBoxSlot* PanelSlot = SkillList->AddChildToHorizontalBox(SkillSlot))
				{
					PanelSlot->SetPadding(20.0f);
					PanelSlot->SetSize(ESlateSizeRule::Fill);
					PanelSlot->SetHorizontalAlignment(HAlign_Fill);
					PanelSlot->SetVerticalAlignment(VAlign_Fill);
				}
				SkillSlot->UpdateUI();
			}
		}
	}
}

void UUI_PlayerSkillSystem::UpdatePlayerSkillSlot(const FGuid &PlayerSKillSlotGUID, bool bInCD)
{
	for (UPanelSlot *PanelSlot : SkillList->GetSlots())
	{
		if (UUI_SkillSlot *SkillSlot = Cast<UUI_SkillSlot>(PanelSlot->Content))
		{
			if (SkillSlot->GUID == PlayerSKillSlotGUID)
			{
				if (bInCD)
				{
					SkillSlot->DrawSlotCD(SkillSlot->GetPlayerSkillData()->GetCDPercent());
				}
				else
				{
					SkillSlot->DrawSlotCD(0.f);
				}

				SkillSlot->UpdateSloInfo(SkillSlot->GetPlayerSkillData()->SkillNumber, SkillSlot->GetPlayerSkillData()->CDTime);

				break;
			}
		}
	}
}
