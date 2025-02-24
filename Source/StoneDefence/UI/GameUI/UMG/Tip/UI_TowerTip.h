// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/UI_RuleOfTheWidget.h"
#include "UI_TowerTip.generated.h"

class UTextBlock;
class UMultiLineEditableTextBox;
struct FCharacterData;
class UProgressBar;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_TowerTip : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
		UTextBlock* LVBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterNameBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ComsumeGlodBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterHealthBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterAttackBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterArmorBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterAttackSpeedBlock;

	UPROPERTY(meta = (BindWidget))
		UProgressBar *EPBar;

	UPROPERTY(meta = (BindWidget))
		UMultiLineEditableTextBox* IntroductionBox;

public:
	void InitTip(const FCharacterData &InData);
};
