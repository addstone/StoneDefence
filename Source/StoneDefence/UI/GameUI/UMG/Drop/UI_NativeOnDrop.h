// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Core/UI_RuleOfTheWidget.h"
#include "UI_NativeOnDrop.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_NativeOnDrop : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
