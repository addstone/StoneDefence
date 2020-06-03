// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SimpleGameUserSettings.h"

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
