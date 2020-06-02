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
		UTextBlock *Number;

public:
	virtual void NativeConstruct() override;

	virtual void OnClickedWidget();

	FPlayerSkillData *GetPlayerSkillData();

	void UpdateUI();

	FORCEINLINE int32 GetKeyNumber() const { return KeyNumber; }
private:
	int32 KeyNumber;
};
