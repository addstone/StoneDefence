// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MainHall.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI_HallMenuSystem.h"
#include "UI_ArchivesSystem.h"
#include "UI_GameSettingsSystem.h"
#include "UI_TutoriaSystem.h"
#include "Components/SizeBox.h"
#include "SimplePopupUtils.h"
#include "../../../StoneDefenceUtils.h"

#define  LOCTEXT_NAMESPACE "UUI_MainHall"

void UUI_MainHall::NativeConstruct()//为什么这样写，直接在UI_HallMenuSystem里边用
{
	Super::NativeConstruct();

	if (HallMenuSystem)
	{
		//GameStart
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::GameStart);
			HallMenuSystem->BindGameStart(Delegate);
		}

		//SecretTerritory
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::SecretTerritory);
			HallMenuSystem->BindSecretTerritory(Delegate);
		}

		//History
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::History);
			HallMenuSystem->BindHistory(Delegate);
		}

		//GameSettings
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::GameSettings);
			HallMenuSystem->BindGameSettings(Delegate);
		}

		//TutorialWebsite
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::TutorialWebsite);
			HallMenuSystem->BindTutorialWebsite(Delegate);
		}

		//Browser
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::Browser);
			HallMenuSystem->BindBrowser(Delegate);
		}

		//SpecialContent
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::SpecialContent);
			HallMenuSystem->BindSpecialContent(Delegate);
		}

		//QuitGame
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::QuitGame);
			HallMenuSystem->BindQuitGame(Delegate);
		}
	}
}

void UUI_MainHall::GameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "SelectLevel");
}

void UUI_MainHall::SecretTerritory()
{

}

void UUI_MainHall::History()
{
	//绑定窗口
	if (UUI_ArchivesSystem *ArchivesSystem = StoneDefenceUtils::CreateAssistWidget<UUI_MainHall, UUI_ArchivesSystem>(this, ArchivesSystemClass, BoxList))
	{
		ArchivesSystem->BindWindows(
			[&](FSimpleDelegate Delegate)
		{
			SimplePopupUtils::CreatePopup(
				GetWorld(),
				PopupClass,
				LOCTEXT("DeleteSaveSlot", "Are you sure you want to delete this archive ?"),
				ESimplePopupType::TWO,
				10.f,
				Delegate);
		});

		ArchivesSystem->InitArchivesSystem(EArchivesState::LOAD);
	}

}

void UUI_MainHall::GameSettings()
{
	StoneDefenceUtils::CreateAssistWidget<UUI_MainHall, UUI_GameSettingsSystem>(this, GameSettingsClass, BoxList);
}

void UUI_MainHall::TutorialWebsite()
{
	StoneDefenceUtils::CreateAssistWidget<UUI_MainHall, UUI_TutoriaSystem>(this, TutoriaSystemClass, BoxList);
}

void UUI_MainHall::Browser()
{

}

void UUI_MainHall::SpecialContent()
{

}

void UUI_MainHall::QuitGame()
{

}
#undef LOCTEXT_NAMESPACE