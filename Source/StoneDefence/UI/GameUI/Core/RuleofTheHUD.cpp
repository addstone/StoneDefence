// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleofTheHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "../UMG/UI_MainScreen.h"
#include "../UMG/Drop/UI_NativeOnDrop.h"

ARuleofTheHUD::ARuleofTheHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_MainScreen> HallMain_BPClass(TEXT("/Game/UI/GameUI/MainScreen_BP"));
	MainScreenClass = HallMain_BPClass.Class;

	static ConstructorHelpers::FClassFinder<UUI_NativeOnDrop> NativeOnDrop_BPClass(TEXT("/Game/UI/GameUI/Drop/Drop_BP"));
	NativeOnDropClass = NativeOnDrop_BPClass.Class;
}

void ARuleofTheHUD::BeginPlay()
{
	Super::BeginPlay();

	MainScreen = CreateWidget<UUI_MainScreen>(GetWorld(), MainScreenClass);
	MainScreen->AddToPlayerScreen(2);

	NativeOnDropPtr = CreateWidget<UUI_NativeOnDrop>(GetWorld(), NativeOnDropClass);
	NativeOnDropPtr->AddToPlayerScreen(0);
}

void ARuleofTheHUD::UpdateInventorySlot(const FGuid &InventorySlotGUID, bool bInCD)
{
	if (MainScreen)
	{
		MainScreen->UpdateInventorySlot(InventorySlotGUID, bInCD);
	}
}

void ARuleofTheHUD::UpdatePlayerSkillSlot(const FGuid &PlayerSKillSlotGUID, bool bInCD)
{
	//if (MainScreen)
	//{
	//	MainScreen->UpdatePlayerSkillSlot(PlayerSKillSlotGUID, bInCD);
	//}
}
