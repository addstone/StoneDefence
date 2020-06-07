// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalConfiguration.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class STONEDEFENCE_API UGlobalConfiguration : public UObject
{
	GENERATED_BODY()
	
public:
	UGlobalConfiguration();

	UPROPERTY(EditDefaultsOnly, Category = "MiniMap")
	float MiniMiniMapSize;

	UPROPERTY(EditDefaultsOnly, Category = "MiniMap")
	float MaxMiniMapSize;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MaxTargetArmLength;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MiniTargetArmLength;
};
