// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ArchivesSystem.h"
#include "Core/SimpleArchivesGlobalVariable.h"
#include "History/UI_ArchivesBar.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"

void UUI_ArchivesSystem::InitArchivesSystem(EArchivesState ArchivesState)
{

}

void UUI_ArchivesSystem::LoadGame()
{

}

void UUI_ArchivesSystem::SaveGame()
{

}

void UUI_ArchivesSystem::NativeConstruct()
{
	Super::NativeConstruct();

	LoadGameButton->OnClicked.AddDynamic(this, &UUI_ArchivesSystem::LoadGame);
	SaveGameButton->OnClicked.AddDynamic(this, &UUI_ArchivesSystem::SaveGame);

	UpdateArchivesSlot();
}

void UUI_ArchivesSystem::NativeDestruct()
{
	Super::NativeDestruct();

	SimpleSlotIndex = INDEX_NONE;
}

void UUI_ArchivesSystem::BindWindows(TFunction<void(FSimpleDelegate)>)
{

}

bool UUI_ArchivesSystem::GetArchivesBarArray(TArray<UUI_ArchivesBar*> &InArchivesBars)
{
	for (UPanelSlot *PanelSlot : SaveSlotList->GetSlots())
	{
		if (UUI_ArchivesBar *ArchivesSlot = Cast<UUI_ArchivesBar>(PanelSlot->Content))
		{
			InArchivesBars.Add(ArchivesSlot);
		}
	}

	return InArchivesBars.Num() > 0;
}

void UUI_ArchivesSystem::UpdateArchivesSlot()
{
	if (ArchivesBarClass)
	{
		TArray<ISimpleArchivesInterface*> &MyArchives = SimpleArchivesGlobalVariable::GetSimpleArchivesArray();
		if (MyArchives.Num())
		{
			for (int32 i = 0; i < MyArchives[0]->GetSaveSlotNumber(); i++)
			{
				if (UUI_ArchivesBar *UIArchivesBar = CreateWidget<UUI_ArchivesBar>(GetWorld(), ArchivesBarClass))
				{
					SaveSlotList->AddChild(UIArchivesBar);
					UIArchivesBar->SlotIndex = i;
					//反向代理
					UIArchivesBar->ReverseProxy = FSimpleDelegate::CreateUObject(this, &UUI_ArchivesSystem::CallAllCkeckBox, UIArchivesBar);

					UIArchivesBar->Update();

					////还原记录的数据
					//if (InSlotList->Slots[i].bSave)
					//{
					//	ResetArchivesBar(UIArchivesBar, &InSlotList->Slots[i]);
					//}

				}
			}
		}
	}
}

void UUI_ArchivesSystem::CallAllCkeckBox(UUI_ArchivesBar* OwnerArchivesBar)
{
	CallAllArchivesBar([&](UUI_ArchivesBar *Tmp)
	{
		if (Tmp != OwnerArchivesBar)
		{
			Tmp->SetCheckBoxState(ECheckBoxState::Unchecked);
		}
	});
}

//void UUI_ArchivesSystem::ResetArchivesBar(UUI_ArchivesBar* InArchivesBar, const FSaveSlot *InData)
//{
//
//}

void UUI_ArchivesSystem::CallAllArchivesBar(TFunction<void(UUI_ArchivesBar* InArchivesBar)> InArchivesBarFunc)
{
	TArray<UUI_ArchivesBar*> InArchivesBars;
	if (GetArchivesBarArray(InArchivesBars))
	{
		for (auto &Tmp : InArchivesBars)
		{
			InArchivesBarFunc(Tmp);
		}
	}
}

void UUI_ArchivesSystem::CallAllArchivesBarBreak(TFunction<bool(UUI_ArchivesBar* InArchivesBar)> InArchivesBarFunc)
{
	TArray<UUI_ArchivesBar*> InArchivesBars;
	if (GetArchivesBarArray(InArchivesBars))
	{
		for (auto &Tmp : InArchivesBars)
		{
			if (InArchivesBarFunc(Tmp))
			{
				break;
			}
		}
	}
}