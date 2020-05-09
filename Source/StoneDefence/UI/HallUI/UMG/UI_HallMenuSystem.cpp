// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HallMenuSystem.h"
#include "Components/Button.h"

void UUI_HallMenuSystem::NativeConstruct()
{
	Super::NativeConstruct();
	GameStartButton			->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindGameStart);
	HistoryButton			->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindHistory);
	GameSettingsButton		->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindGameSettings);
	TutorialWebsiteButton	->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindTutorialWebsite);
	BrowserButton			->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindBrowser);
	QuitGameButton			->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindQuitGame);
}

void UUI_HallMenuSystem::BindGameStart()
{

}

void UUI_HallMenuSystem::BindHistory()
{

}

void UUI_HallMenuSystem::BindGameSettings()
{

}

void UUI_HallMenuSystem::BindTutorialWebsite()
{

}

void UUI_HallMenuSystem::BindBrowser()
{

}

void UUI_HallMenuSystem::BindQuitGame()
{

}
