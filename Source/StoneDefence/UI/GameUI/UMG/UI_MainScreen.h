// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_RuleOfTheWidget.h"
#include "UI_GameSettingsSystem.h"
#include "UI_MainScreen.generated.h"



/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_MainScreen : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
		class UUI_GameMenuSystem* GameMenuSystem;

	UPROPERTY(meta = (BindWidget))
		class UUI_GameInfoPrintSystem* GameInfoPrintSystem;

	UPROPERTY(meta = (BindWidget))
		class UUI_MiniMapSystem* MiniMapSystem;

	UPROPERTY(meta = (BindWidget))
		class UUI_MissionSystem* MissionSystem;

	UPROPERTY(meta = (BindWidget))
		class UUI_PlayerSkillSystem* PlayerSkillSystem;

	UPROPERTY(meta = (BindWidget))
		class UUI_RucksackSystem* RucksackSystem;

	UPROPERTY(meta = (BindWidget))
		class UUI_ToolBarSystem* ToolBarSystem;

	UPROPERTY(meta = (BindWidget))
		class UUI_TowerTip* CharacterTip;

	UPROPERTY(meta = (BindWidget))
		class UImage* FireConcentrationPoint;

	UPROPERTY(meta = (BindWidget))
		class UVerticalBox *NewWindows;

	UPROPERTY(meta = (BindWidget))
		class UButton *SettingsButton;

	UPROPERTY(meta = (BindWidget))
		class USizeBox *BoxList;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_ArchivesSystem> ArchivesSystemClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_GameSettingsSystem> GameSettingsClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_SimplePopup> PopupClass;

public:
	virtual void NativeConstruct() override;

	//Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateInventorySlot(const FGuid &InventorySlotGUID, bool bInCD);

	void UpdatePlayerSkillSlot(const FGuid &PlayerSKillSlotGUID, bool bInCD);

	UFUNCTION()
		void Settings();

	UFUNCTION()
		void SaveGame();

	UFUNCTION()
		void SaveSettings();

	UFUNCTION()
		void ReturnGame();
};
