// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "SimpleGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAMESETTINGS_API USimpleGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

	//�Ƿ�֧����������
	UPROPERTY(config)
		bool bSupportPhysX;

public:
	void SetCurrentLanguage(const FString &NewLanguage);

	static USimpleGameUserSettings* GetSimpleGameUserSettings();

	FString GetCurrentLanguageType();
};
