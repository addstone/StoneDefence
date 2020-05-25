// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Core/GameCore/TowersDefenceGameState.h"
#include "../../Core/GameCore/TowersDefencePlayerState.h"
#include "../../Core/GameCore/TowersDefencePlayerController.h"
#include "UI_RuleOfTheWidget.generated.h"

class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_RuleOfTheWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI" )
		FGuid GUID;

	UWidgetAnimation *GetNameWidgetAnimation(const FString& WidgetAnimationName) const;
	ATowersDefenceGameState *GetGameState();
	ATowersDefencePlayerState *GetPlayerState();
	ATowersDefencePlayerController *GetPlayerController();
};
