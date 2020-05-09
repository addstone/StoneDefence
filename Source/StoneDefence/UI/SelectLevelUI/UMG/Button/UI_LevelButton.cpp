// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_LevelButton.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UUI_LevelButton::NativeConstruct()
{
	Super::NativeConstruct();

	SelectLevelButton->OnClicked.AddDynamic(this, &UUI_LevelButton::SelectLevel);
}

void UUI_LevelButton::SelectLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "TestMap");
}
