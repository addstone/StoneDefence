// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillSlot.h"
#include "Components/Button.h"
#include "../../../../Global/UI_Data.h"
#include "Components/TextBlock.h"

void UUI_SkillSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ClickButton->OnClicked.AddDynamic(this, &UUI_SkillSlot::OnClickedWidget);
	if (PlayerSkillNumber == 9)
	{
		PlayerSkillNumber = 0;
		SlotNumber->SetText(FText::FromString(FString::FromInt(PlayerSkillNumber)));
	}
	else
	{
		SlotNumber->SetText(FText::FromString(FString::FromInt(++PlayerSkillNumber)));
	}
	
}

void UUI_SkillSlot::OnClickedWidget()
{

}
