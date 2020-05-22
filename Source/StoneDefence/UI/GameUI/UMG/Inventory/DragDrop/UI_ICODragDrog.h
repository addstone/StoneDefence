// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../Core/UI_RuleOfTheWidget.h"
#include "UI_ICODragDrog.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_ICODragDrog : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
		UImage *ICON;

public:

	void DrawICON(UTexture2D *InICON);
};
