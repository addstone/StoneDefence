// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_RuleOfTheWidget.h"
#include "UI_HallMenuSystem.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_HallMenuSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		UButton *GameStartButton;

	UPROPERTY(meta = (BindWidget))
		UButton *HistoryButton;

	UPROPERTY(meta = (BindWidget))
		UButton *GameSettingsButton;

	UPROPERTY(meta = (BindWidget))
		UButton *TutorialWebsiteButton;

	UPROPERTY(meta = (BindWidget))
		UButton *BrowserButton;

	UPROPERTY(meta = (BindWidget))
		UButton *QuitGameButton;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void BindGameStart();
	UFUNCTION()
	void BindHistory();
	UFUNCTION()
	void BindGameSettings();
	UFUNCTION()
	void BindTutorialWebsite();
	UFUNCTION()
	void BindBrowser();
	UFUNCTION()
	void BindQuitGame();
	
};
