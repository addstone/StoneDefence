// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI_SimpleGameSettingsCore.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "SimpleGameSettingsMacro.h"

void UUI_SimpleGameSettingsCore::UpdateAttibeLevel(USlider *NewSlider, UTextBlock *NewBlock)
{

}

void UUI_SimpleGameSettingsCore::UpdateAttibe(USlider *NewSlider, UTextBlock *NewBlock)
{
	float FloatNumber = NewSlider->GetValue() * 10.f;
	FString StringFloatNumberText = FString::Printf(TEXT("%.2f"), FloatNumber);
	NewBlock->SetText(FText::FromString(StringFloatNumberText));
}

void UUI_SimpleGameSettingsCore::BindChangedValue(USlider *NewSlider)
{
	NewSlider->OnValueChanged.AddDynamic(this, &UUI_SimpleGameSettingsCore::ChangedValue);
}

void UUI_SimpleGameSettingsCore::BindSelectionChanged(UComboBoxString *BoxString)
{
	BoxString->OnSelectionChanged.AddDynamic(this, &UUI_SimpleGameSettingsCore::SelectionChanged);
}

void UUI_SimpleGameSettingsCore::SetSettingsLevel(USlider* InSlider, UTextBlock *NewBlock, TFunction<void(float InLevel)> InFunc)
{
	InFunc(InSlider->GetValue() * SCAL_ABILITY_QUALITY_LEVEL);
	UpdateAttibe(InSlider, NewBlock);
}

void UUI_SimpleGameSettingsCore::LoadSettingsLevel(USlider* InSlider, UTextBlock *NewBlock, TFunction<float()> InFunc)
{
	InSlider->SetValue(InFunc() / (float)SCAL_ABILITY_QUALITY_LEVEL);
	UpdateAttibe(InSlider, NewBlock);
}

void UUI_SimpleGameSettingsCore::LoadBoxString(UComboBoxString* InBoxString, TFunction<FString()> InFunc)
{
	InBoxString->SetSelectedOption(InFunc());
}
