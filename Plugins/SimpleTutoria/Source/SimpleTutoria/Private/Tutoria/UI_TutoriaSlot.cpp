// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutoria/UI_TutoriaSlot.h"
#include "Components/Button.h"
#include "GlobalTutoriaProxy.h"

UUI_TutoriaSlot::UUI_TutoriaSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Index = INDEX_NONE;
}

bool UUI_TutoriaSlot::IsIndexValid()
{
	return Index != INDEX_NONE;
}

void UUI_TutoriaSlot::Play()
{
	if (SimpleTutoriaMulticastDelegate.IsBound())
	{
		if (SimpleTutoriaMulticastDelegate.Execute(Index))
		{

		}
	}
}

void UUI_TutoriaSlot::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddDynamic(this, &UUI_TutoriaSlot::Play);
}
