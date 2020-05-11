// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/RuleOfTheAIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API AMonsterAIController : public ARuleOfTheAIController
{
	GENERATED_BODY()
	
public:
	virtual AActor *FindTarget();
};
