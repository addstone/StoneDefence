// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Health.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/WrapBox.h"

void UUI_Health::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_Health::SetTitle(const FString &Msg)
{
	Title->SetText(FText::FromString(Msg));
}

void UUI_Health::SetHealth(float HealthValue)
{
	Health->SetPercent(HealthValue);
}

void UUI_Health::AddSkillSlot(FGuid SkillID)
{
	
}

bool UUI_Health::RemoveSkillSlot(FGuid SkillID)
{
	return false;
}
