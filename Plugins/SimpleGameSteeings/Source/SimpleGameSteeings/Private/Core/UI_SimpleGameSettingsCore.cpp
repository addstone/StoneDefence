// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI_SimpleGameSettingsCore.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"

void UUI_SimpleGameSettingsCore::UpdateAttibeLevel(USlider *NewSlider, UTextBlock *NewBlock)
{

}

void UUI_SimpleGameSettingsCore::UpdateAttibe(USlider *NewSlider, UTextBlock *NewBlock)
{
	float FloatNumber = NewSlider->GetValue() * 0.f;
	FString StringFloatNumberText = FString::Printf(TEXT(/*"%.2f"*/"%02d"), FloatNumber);
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
