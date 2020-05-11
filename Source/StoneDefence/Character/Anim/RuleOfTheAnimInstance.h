// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RuleOfTheAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API URuleOfTheAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	URuleOfTheAnimInstance();

	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float Deltaseconds);
	
protected:
	bool IsDelayUpdate(float Deltaseconds);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttrubute")
		bool bDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttrubute")
		bool bAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttrubute")
		float Speed;

private:

	float CurrentTime;
	bool bDelayTime;
};
