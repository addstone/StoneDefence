// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_TowerTip.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/ProgressBar.h"
#include "../../../../Data/CharacterData.h"

void UUI_TowerTip::InitTip(const FCharacterData &InData)
{
	LVBlock->SetText(FText::AsNumber(InData.Lv));
	CharacterNameBlock->SetText(FText::FromName(InData.Name));
	ComsumeGlodBlock->SetText(FText::AsNumber(InData.Glod));
	CharacterHealthBlock->SetText(FText::AsNumber(InData.GetMaxHealth()));
	CharacterAttackBlock->SetText(FText::AsNumber(InData.GetAttack()));
	CharacterArmorBlock->SetText(FText::AsNumber(InData.GetArmor()));
	CharacterAttackSpeedBlock->SetText(FText::AsNumber(InData.GetAttackSpeed()));
	IntroductionBox->SetText(InData.Introduction);
	EPBar->SetPercent(InData.GetEPPercent());
}
