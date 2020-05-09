// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_SelectLevelMain.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Button/UI_LevelButton.h"

void UUI_SelectLevelMain::NativeConstruct()
{
	Super::NativeConstruct();

	InitSelectLevelButton();

	ReturnMenuButton->OnClicked.AddDynamic(this, &UUI_SelectLevelMain::ReturnMenu);
}

void UUI_SelectLevelMain::InitSelectLevelButton()
{
	if (SelectMap)
	{
		TArray<UPanelSlot*> PanelSlotArray = SelectMap->GetSlots();
		for (UPanelSlot *PanelSlotElement : PanelSlotArray)
		{
			if (UUI_LevelButton *LevelButtonArp = Cast<UUI_LevelButton>(PanelSlotElement->Content))
			{
				AllLevelButton.Add(LevelButtonArp);
			}
		}
	}
}

void UUI_SelectLevelMain::ReturnMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "HallMap");
}
