// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Core/ManageCore.h"
#include "GlobalManagement.generated.h"

class UGlobalConfiguration;
class UGlobalResource;
/**
 * 
 */

USTRUCT()
struct STONEDEFENCE_API FGlobalManagement
{
	GENERATED_USTRUCT_BODY()

	FGlobalManagement();

	void Constructor(UWorld *InWorld);
	void Destructural();

	const UGlobalResource *GetGlobalResource();
	const UGlobalConfiguration *GetGlobalConfiguration();
private:
	UPROPERTY()
	UGlobalResource *GlobalResource;

	UPROPERTY()
	UGlobalConfiguration *GlobalConfiguration;
};
