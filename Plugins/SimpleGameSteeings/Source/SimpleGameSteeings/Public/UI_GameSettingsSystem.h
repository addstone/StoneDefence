// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_GameSettingsSystem.generated.h"

class UCheckBox;
class UButton;
class UWidgetSwitcher;
class UUI_GameSettingsVideo;
class UUI_GameSetingsAudio;
class UUI_GameSettingsGameSetting;
/**
 * 
 */
UCLASS()
class SIMPLEGAMESETTINGS_API UUI_GameSettingsSystem : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
		UCheckBox* AudioSettingBox;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* VideoSettingsBox;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* GameSettingsBox;

	UPROPERTY(meta = (BindWidget))
		UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
		UButton* ReturnMenuButton;

	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* SettingsListWitcher;

	UPROPERTY(meta = (BindWidget))
		UUI_GameSettingsVideo* GameSettingsVideo;

	UPROPERTY(meta = (BindWidget))
		UUI_GameSetingsAudio* GameSetingsAudio;

	UPROPERTY(meta = (BindWidget))
		UUI_GameSettingsGameSetting* GameSettingsGameSetting;
public:
	virtual void NativeConstruct()override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
