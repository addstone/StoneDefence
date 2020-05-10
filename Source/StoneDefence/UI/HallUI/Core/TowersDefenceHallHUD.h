// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowersDefenceHallHUD.generated.h"

class UUI_MainHall;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefenceHallHUD : public AHUD
{
	GENERATED_BODY()
public:
	ATowersDefenceHallHUD();

	virtual void BeginPlay() override;
	
private:
	TSubclassOf<UUI_MainHall> MainHallClass;
	UUI_MainHall *MainHall;
};
