// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceHallHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "../UMG/UI_MainHall.h"

ATowersDefenceHallHUD::ATowersDefenceHallHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_MainHall> HallMain_BPClass(TEXT("/Game/UI/HallUI/HallMain_BP"));
	MainHallClass = HallMain_BPClass.Class;
}

void ATowersDefenceHallHUD::BeginPlay()
{
	Super::BeginPlay();

	MainHall = CreateWidget<UUI_MainHall>(GetWorld(), MainHallClass);
	MainHall->AddToViewport();
}