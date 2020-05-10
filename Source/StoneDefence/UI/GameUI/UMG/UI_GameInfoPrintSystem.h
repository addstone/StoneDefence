// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drop/UI_NativeOnDrop.h"
#include "UI_GameInfoPrintSystem.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_GameInfoPrintSystem : public UUI_NativeOnDrop
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TDGameLog;

public:

	virtual void NativeConstruct()override;
	
};
