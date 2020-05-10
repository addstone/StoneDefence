// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_HallMenuSystem.h"
#include "Kismet/GameplayStatics.h"

void UUI_HallMenuSystem::NativeConstruct()
{
	Super::NativeConstruct();
	//GameStartButton			->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindGameStart);
	//SecretTerritoryButton	->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindSecretTerritory);
	//HistoryButton			->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindHistory);
	//GameSettingsButton		->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindGameSettings);
	//TutorialWebsiteButton	->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindTutorialWebsite);
	//BrowserButton			->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindBrowser);
	//SpecialContentButton	->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindSpecialContent);
	//QuitGameButton			->OnClicked.AddDynamic(this, &UUI_HallMenuSystem::BindQuitGame);
}

void UUI_HallMenuSystem::BindGameStart(FOnButtonClickedEvent ClickedEvent)
{
	GameStartButton->OnClicked = ClickedEvent;
}

void UUI_HallMenuSystem::BindSecretTerritory(FOnButtonClickedEvent ClickedEvent)
{
	SecretTerritoryButton->OnClicked = ClickedEvent;
}

void UUI_HallMenuSystem::BindHistory(FOnButtonClickedEvent ClickedEvent)
{
	HistoryButton->OnClicked = ClickedEvent;
}

void UUI_HallMenuSystem::BindGameSettings(FOnButtonClickedEvent ClickedEvent)
{
	GameSettingsButton->OnClicked = ClickedEvent;
}

void UUI_HallMenuSystem::BindTutorialWebsite(FOnButtonClickedEvent ClickedEvent)
{
	TutorialWebsiteButton->OnClicked = ClickedEvent;
}

void UUI_HallMenuSystem::BindBrowser(FOnButtonClickedEvent ClickedEvent)
{
	BrowserButton->OnClicked = ClickedEvent;
}

void UUI_HallMenuSystem::BindSpecialContent(FOnButtonClickedEvent ClickedEvent)
{
	SpecialContentButton->OnClicked = ClickedEvent;
}

void UUI_HallMenuSystem::BindQuitGame(FOnButtonClickedEvent ClickedEvent)
{
	QuitGameButton->OnClicked = ClickedEvent;
}

