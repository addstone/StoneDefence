// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/UI_RuleOfTheWidget.h"
#include "UI_CharacterSkillSlot.generated.h"

class UBorder;
class UImage;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_CharacterSkillSlot : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	

	UPROPERTY(meta = (BindWidget))
		UBorder* Icon;

	UPROPERTY(meta = (BindWidget))
		UImage* CD;

	//CD��̬����
	UPROPERTY()
		class UMaterialInstanceDynamic* CDMaterialDynamic;

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetTexture(UTexture2D *InTexture);

	void UpdateCD(float SkillCD);

	FSkillData *GetSkillData();
};
