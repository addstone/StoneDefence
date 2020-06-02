// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drop/UI_NativeOnDrop.h"
#include "UI_PlayerSkillSystem.generated.h"


class UUI_SkillSlot;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_PlayerSkillSystem : public UUI_NativeOnDrop
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
		UHorizontalBox *SkillList;

	//UPROPERTY(meta=(BindWidget))
	//	UUI_SkillSlot *FreezeSkill;

	//UPROPERTY(meta = (BindWidget))
	//	UUI_SkillSlot *ExplosionSkill;

	//UPROPERTY(meta = (BindWidget))
	//	UUI_SkillSlot *RecoverySkill;

	//UPROPERTY(meta = (BindWidget))
	//	UUI_SkillSlot *RecoveryMainTowersSkill;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUI_SkillSlot> SkillSlotClass;
public:
	virtual void NativeConstruct() override;

	void LayoutPlayerSkillSlot();

	void UpdatePlayerSkillSlot(const FGuid &PlayerSKillSlotGUID, bool bInCD);
private:
	FKey FreezeSkillKey;
	FKey ExplosionSkillKey;
	FKey RecoverySkillKey;
	FKey RecoveryMainTowersSkillKey;
};
