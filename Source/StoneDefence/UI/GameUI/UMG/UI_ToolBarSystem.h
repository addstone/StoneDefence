// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drop/UI_NativeOnDrop.h"
#include "UI_ToolBarSystem.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_ToolBarSystem : public UUI_NativeOnDrop
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameGlob;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TowersDeathNumber;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameCount;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* KillSoldier;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameLevelSurplusQuantity;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* GSQProgressBar;

public:
	virtual void NativeConstruct()override;

	//Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	FString GetCurrentCount(float NewTimeCount);
	
};
