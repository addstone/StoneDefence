// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ArchivesSystem.h"
#include "Core/SimpleArchivesGlobalVariable.h"
#include "Histroy/UI_ArchivesBar.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Data/SimpleArchivesList.h"

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

}

void UUI_ArchivesSystem::NativeDestruct()
{

}

void UUI_ArchivesSystem::BindWindows(TFunction<void(FSimpleDelegate)>)
{

}

bool UUI_ArchivesSystem::GetArchivesBarArray(TArray<UUI_ArchivesBar*> &InArchivesBars)
{

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

				}
			}
		}
	}
}

void UUI_ArchivesSystem::CallAllCkeckBox(UUI_ArchivesBar* OwnerArchivesBar)
{

}

void UUI_ArchivesSystem::ResetArchivesBar(UUI_ArchivesBar* InArchivesBar, const FSaveSlot *InData)
{

}

void UUI_ArchivesSystem::CallAllArchivesBar(TFunction<void(UUI_ArchivesBar* InArchivesBar)>)
{

}

void UUI_ArchivesSystem::CallAllArchivesBarBreak(TFunction<bool(UUI_ArchivesBar* InArchivesBar)>)
{

}
