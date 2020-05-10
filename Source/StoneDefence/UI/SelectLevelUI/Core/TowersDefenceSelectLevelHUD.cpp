// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceSelectLevelHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "../UMG/UI_SelectLevelMain.h"

ATowersDefenceSelectLevelHUD::ATowersDefenceSelectLevelHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_SelectLevelMain> SelectMain_BPClass(TEXT("/Game/UI/SelectUI/SelectMain_BP"));
	SelectMainClass = SelectMain_BPClass.Class;
}

void ATowersDefenceSelectLevelHUD::BeginPlay()
{
	Super::BeginPlay();

	SelectLevelMain = CreateWidget<UUI_SelectLevelMain>(GetWorld(), SelectMainClass);
	SelectLevelMain->AddToViewport();
}
