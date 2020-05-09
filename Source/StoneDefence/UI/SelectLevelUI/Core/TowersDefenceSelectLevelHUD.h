// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowersDefenceSelectLevelHUD.generated.h"

class UUI_SelectLevelMain;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefenceSelectLevelHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATowersDefenceSelectLevelHUD();

	virtual void BeginPlay() override;
private:
	TSubclassOf<UUI_SelectLevelMain> SelectMainClass;
	UUI_SelectLevelMain *SelectLevelMain;
};
