// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/UI_RuleOfTheWidget.h"
#include "UI_LevelButton.generated.h"

class UBorder;
class UButton;
class UProgressBar;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_LevelButton : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
		UBorder* LevelBorder;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* LevelProBar;

	UPROPERTY(meta = (BindWidget))
		UButton* SelectLevelButton;
public:
	virtual void NativeConstruct()override;

	UFUNCTION()
		void SelectLevel();
};
