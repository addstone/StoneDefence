// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_RuleOfTheWidget.h"
#include "../../Core/GameCore/TowersDefenceGameState.h"

UUI_RuleOfTheWidget::UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GUID = FGuid::NewGuid();
}

UWidgetAnimation* UUI_RuleOfTheWidget::GetNameWidgetAnimation(const FString& WidgetAnimationName) const
{
	if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGenerated = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		TArray<UWidgetAnimation*> TArrayAnimations = WidgetBlueprintGenerated->Animations;
		UWidgetAnimation** MyTempAnimation = TArrayAnimations.FindByPredicate([&](const UWidgetAnimation* OurAnimation) {return OurAnimation->GetFName().ToString() == (WidgetAnimationName + FString("_INST")); });
		return *MyTempAnimation;
	}

	return nullptr;
}

ATowersDefenceGameState * UUI_RuleOfTheWidget::GetGameState()
{
	if (GetWorld())
	{
		return GetWorld()->GetGameState<ATowersDefenceGameState>();
	}

	return nullptr;
}

ATowersDefencePlayerState * UUI_RuleOfTheWidget::GetPlayerState()
{
	if (GetPlayerController())
	{
		return GetPlayerController()->GetPlayerState<ATowersDefencePlayerState>();
	}

	return nullptr;
}

ATowersDefencePlayerController * UUI_RuleOfTheWidget::GetPlayerController()
{
	if (GetWorld())
	{
		return GetWorld()->GetFirstPlayerController<ATowersDefencePlayerController>();
	}

	return nullptr;
}
