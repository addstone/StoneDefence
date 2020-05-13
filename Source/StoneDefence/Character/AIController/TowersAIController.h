// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/RuleOfTheAIController.h"
#include "TowersAIController.generated.h"

class ARuleOfTheCharacter;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersAIController : public ARuleOfTheAIController
{
	GENERATED_BODY()
	

public:
	ATowersAIController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual AActor *FindTarget();

protected:

	void BTService_FindTarget();
	virtual void AttackTarget(ARuleOfTheCharacter *InTarget);

protected:

	//这里面是我们的怪物
	UPROPERTY()
		TArray<class ARuleOfTheCharacter*> TArrayMonsters;

	float HeartbeatDiagnosis;

	//TWeakObjectPtr<ARuleOfTheCharacter> Target;统一在父类中
};
