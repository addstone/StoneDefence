// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettings/UI_GameSettingsVideo.h"
#include "Core/SimpleGameUserSettings.h"
#include "Components/ComboBoxString.h"
#include "Components/CheckBox.h"
#include "Components/SpinBox.h"
#include "Core/UI_SimpleGameSettingsCore.h"
#include "SimpleGameSettingsMacro.h"


void UUI_GameSettingsVideo::NativeConstruct()
{
	Super::NativeConstruct();

	FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::FullScreenCheckClickedBox);
	WindowScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::WindowScreenCheckClickedBox);
	SupportPhysXCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::SupportPhysXCheckClickedBox);
	VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::VSyncCheckClickedBox);
	HDRDisplayCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::EnableHDRDisplayOutput);
	FrameRateLimitSpinBox->OnValueChanged.AddDynamic(this, &UUI_GameSettingsVideo::SetFrameRateLimit);

	BindChangedValue(AntiAliasingSlider);
	BindChangedValue(ShadowQualitySlider);
	BindChangedValue(TextureQualitySlider); 
	BindChangedValue(PostProcessingSlider); 
	BindChangedValue(EffectsSlider);
	BindChangedValue(FoliageSlider);
	BindChangedValue(ViewDistanceSlider);
	BindChangedValue(ShadingSlider);

	BindSelectionChanged(ResolutionBoxString);
	BindSelectionChanged(LanguageString);
}

void UUI_GameSettingsVideo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_GameSettingsVideo::SaveSettings()
{
	SetSettingsLevel(TextureQualitySlider, TextureQualityText,
		[](float InLevel)
	{
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetTextureQuality(InLevel);
	});

	SetSettingsLevel(ShadowQualitySlider, ShadowQualityText,
		[](float InLevel)
	{
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetShadowQuality(InLevel);
	});

	SetSettingsLevel(AntiAliasingSlider, AntiAliasingText,
		[](float InLevel)
	{
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetAntiAliasingQuality(InLevel);
	});

	SetSettingsLevel(PostProcessingSlider, PostProcessingText,
		[](float InLevel)
	{
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetPostProcessingQuality(InLevel);
	});

	SetSettingsLevel(EffectsSlider, EffectsText,
		[](float InLevel)
	{
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetVisualEffectQuality(InLevel);
	});

	SetSettingsLevel(FoliageSlider, FoliageText,
		[](float InLevel)
	{
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetFoliageQuality(InLevel);
	});

	SetSettingsLevel(ViewDistanceSlider, ViewDistanceText,
		[](float InLevel)
	{
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetViewDistanceQuality(InLevel);
	});

	SetSettingsLevel(ShadingSlider, ShadingText,
		[](float InLevel)
	{
		if (InLevel != USimpleGameUserSettings::GetSimpleGameUserSettings()->GetOverallScalabilityLevel())
		{
			USimpleGameUserSettings::GetSimpleGameUserSettings()->SetViewDistanceQuality(InLevel);
		}		
	});
	
}

void UUI_GameSettingsVideo::LoadSettings()
{
	LoadSettingsLevel(AntiAliasingSlider, AntiAliasingText,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetAntiAliasingQuality();
	});

	LoadSettingsLevel(TextureQualitySlider, TextureQualityText,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetTextureQuality();
	});

	LoadSettingsLevel(ShadowQualitySlider, ShadowQualityText,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetShadowQuality();
	});

	LoadSettingsLevel(PostProcessingSlider, PostProcessingText,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetPostProcessingQuality();
	});

	LoadSettingsLevel(EffectsSlider, EffectsText,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetVisualEffectQuality();
	});

	LoadSettingsLevel(ViewDistanceSlider, ViewDistanceText,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetViewDistanceQuality();
	});

	LoadSettingsLevel(FoliageSlider, FoliageText,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetFoliageQuality();
	});

	LoadSettingsLevel(ShadingSlider, ShadingText,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetShadingQuality();
	});

	LoadBoxString(ResolutionBoxString,
		[]()
	{
		FIntPoint ResolutionPoint = USimpleGameUserSettings::GetSimpleGameUserSettings()->GetScreenResolution();
		return FString::Printf(TEXT("%ix%i"), ResolutionPoint.X, ResolutionPoint.Y);
	});

	LoadBoxString(LanguageString,
		[]()
	{
		return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetCurrentLanguageType();
	});

	EWindowMode::Type InModeType = USimpleGameUserSettings::GetSimpleGameUserSettings()->GetFullscreenMode();
	switch (InModeType)
	{
	case EWindowMode::WindowedFullscreen:
	case EWindowMode::Fullscreen:
		FullScreenCheckBox->SetCheckedState(ECheckBoxState::Checked);
		WindowScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		break;
	case EWindowMode::Windowed:
		FullScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		WindowScreenCheckBox->SetCheckedState(ECheckBoxState::Checked);
		break;
	case EWindowMode::NumWindowModes:
		break;
	}



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
	USimpleGameUserSettings::GetSimpleGameUserSettings()->SetVSyncEnabled(ClickedWidget);
}

void UUI_GameSettingsVideo::EnableHDRDisplayOutput(bool ClickedWidget)
{
	USimpleGameUserSettings::GetSimpleGameUserSettings()->EnableHDRDisplayOutput(ClickedWidget, DisplayNitsSpinBox->GetValue());
}

void UUI_GameSettingsVideo::SetFrameRateLimit(float NewValue)
{
	USimpleGameUserSettings::GetSimpleGameUserSettings()->SetFrameRateLimit(NewValue);
}

void UUI_GameSettingsVideo::ChangedValue(float InValue)
{
	UpdateAttibeLevel(AntiAliasingSlider, AntiAliasingText);	//锯齿
	UpdateAttibeLevel(ShadowQualitySlider, ShadowQualityText);//阴影
	UpdateAttibeLevel(TextureQualitySlider, TextureQualityText);//贴图
	UpdateAttibeLevel(PostProcessingSlider, PostProcessingText);//后期
	UpdateAttibeLevel(EffectsSlider, EffectsText);//特效
	UpdateAttibeLevel(FoliageSlider, FoliageText);//植被
	UpdateAttibeLevel(ViewDistanceSlider, ViewDistanceText);//视距
	UpdateAttibeLevel(ShadingSlider, ShadingText);//Shading
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
