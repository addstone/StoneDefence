// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SimpleGameUserSettings.h"
#include "../Private/Internationalization/LegacyInternationalization.h"
#include "Internationalization/Culture.h"

void USimpleGameUserSettings::SetCurrentLanguage(const FString &NewLanguage)
{
	if (NewLanguage == "English" || NewLanguage == "en")
	{
		FInternationalization::Get().SetCurrentCulture("en-US");
	}
	else if (NewLanguage == "Chinese" || NewLanguage == "zh" || NewLanguage == "zh-CN")
	{
		FInternationalization::Get().SetCurrentCulture("zh-Hans-CN");
	}
}

USimpleGameUserSettings* USimpleGameUserSettings::GetSimpleGameUserSettings()
{
	return GEngine != NULL ? (Cast<USimpleGameUserSettings>(GEngine->GetGameUserSettings())) : NULL;
}

FString USimpleGameUserSettings::GetCurrentLanguageType()
{
	if (FInternationalization::Get().GetCurrentCulture().Get().GetName() == "en" ||
		FInternationalization::Get().GetCurrentCulture().Get().GetName() == "en-US")
	{
		return "English";
	}
	else if (FInternationalization::Get().GetCurrentCulture().Get().GetName() == "zh" ||
		FInternationalization::Get().GetCurrentCulture().Get().GetName() == "zh-CN" ||
		FInternationalization::Get().GetCurrentCulture().Get().GetName() == "zh-Hans-CN")
	{
		return "Chinese";
	}

	return "English";
}
