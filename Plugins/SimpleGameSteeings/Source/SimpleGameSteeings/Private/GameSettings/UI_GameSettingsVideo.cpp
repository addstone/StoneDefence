// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettings/UI_GameSettingsVideo.h"
#include "Core/SimpleGameUserSettings.h"
#include "Components/ComboBoxString.h"
#include "Components/CheckBox.h"
#include "Components/SpinBox.h"


void UUI_GameSettingsVideo::NativeConstruct()
{
	Super::NativeConstruct();

	FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::FullScreenCheckClickedBox);
	WindowScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::WindowScreenCheckClickedBox);
	SupportPhysXCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::SupportPhysXCheckClickedBox);
	//VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::VSyncCheckClickedBox);
	//HDRDisplayCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::EnableHDRDisplayOutput);
	//FrameRateLimitSpinBox->OnValueChanged.AddDynamic(this, &UUI_GameSettingsVideo::SetFrameRateLimit);

	BindChangedValue(AntiAliasingSlider);
	BindChangedValue(ShadowQualitySlider);
	BindChangedValue(TextureQualitySlider); 
	BindChangedValue(PostProcessingSlider); 
	BindChangedValue(EffectsSlider);
	BindChangedValue(FoliageSlider);
	BindChangedValue(ViewDistanceSlider);
	BindChangedValue(OverallScalabilityLevelSliderSlider);

	BindSelectionChanged(ResolutionBoxString);
	BindSelectionChanged(LanguageString);
}

void UUI_GameSettingsVideo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_GameSettingsVideo::SaveSettings()
{

}

void UUI_GameSettingsVideo::LoadSettings()
{

}

void UUI_GameSettingsVideo::FullScreenCheckClickedBox(bool ClickedWidget)
{
	FullScreenCheckBox->SetCheckedState(ECheckBoxState::Checked);
	WindowScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	USimpleGameUserSettings::GetSimpleGameUserSettings()->SetFullscreenMode(EWindowMode::Fullscreen);
}

void UUI_GameSettingsVideo::WindowScreenCheckClickedBox(bool ClickedWidget)
{
	FullScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	WindowScreenCheckBox->SetCheckedState(ECheckBoxState::Checked);
	USimpleGameUserSettings::GetSimpleGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
}

void UUI_GameSettingsVideo::SupportPhysXCheckClickedBox(bool ClickedWidget)
{

}

void UUI_GameSettingsVideo::VSyncCheckClickedBox(bool ClickedWidget)
{

}

void UUI_GameSettingsVideo::EnableHDRDisplayOutput(bool ClickedWidget)
{

}

void UUI_GameSettingsVideo::SetFrameRateLimit(float NewValue)
{

}

void UUI_GameSettingsVideo::ChangedValue(float InValue)
{
	UpdateAttibe(AntiAliasingSlider, AntiAliasingText);	//锯齿
	UpdateAttibe(ShadowQualitySlider, ShadowQualityText);//阴影
	UpdateAttibe(TextureQualitySlider, TextureQualityText);//贴图
	UpdateAttibe(PostProcessingSlider, PostProcessingText);//后期
	UpdateAttibe(EffectsSlider, EffectsText);//特效
	UpdateAttibe(FoliageSlider, FoliageText);//植被
	UpdateAttibe(ViewDistanceSlider, ViewDistanceText);//视距
	UpdateAttibe(OverallScalabilityLevelSliderSlider, OverallScalabilityLevelSliderText);
}

void UUI_GameSettingsVideo::SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	//更新语言
	{
		FString LanguageTmp = LanguageString->GetSelectedOption();
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetCurrentLanguage(LanguageTmp);
	}

	//更新分辨率
	{
		FIntPoint ResolutionPoint;
		FString ResolutionTmp = ResolutionBoxString->GetSelectedOption();
		FString R, L;
		ResolutionTmp.Split(TEXT("x"), &R, &L);
		ResolutionPoint.X = FCString::Atoi(*R);
		ResolutionPoint.Y = FCString::Atoi(*L);
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetScreenResolution(ResolutionPoint);
	}
}
