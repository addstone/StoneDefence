// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RuleOfThePlayerState.h"
#include "TowersDefencePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefencePlayerState : public ARuleOfThePlayerState
{
	GENERATED_BODY()
	

protected:
	UPROPERTY()
		UPlayerSaveData *SaveData;
};
