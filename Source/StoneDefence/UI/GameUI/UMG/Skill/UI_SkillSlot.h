// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Slot.h"
#include "UI_SkillSlot.generated.h"

class UImage;
class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_SkillSlot : public UUI_Slot
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
		UImage *SkillIcon;

	UPROPERTY(meta = (BindWidget))
		UImage *SkillIconCD;

	UPROPERTY(meta = (BindWidget))
		UTextBlock *SkillNumber;

	UPROPERTY(meta = (BindWidget))
		UTextBlock *KeyValueNumber;

	UPROPERTY(meta = (BindWidget))
		UTextBlock *SkillCDValue;

	UPROPERTY(meta = (BindWidget))
		UButton *ClickButton;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnClickedWidget();
};
