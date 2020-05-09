// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tool/ScreenMove.h"
#include "TowersDefencePlayerController.generated.h"


/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefencePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATowersDefencePlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetInputModeGameAndUI();

	virtual void SetupInputComponent() override;
	void MouseWheelUP();
	void MouseWheelDown();

protected:
	FScreenMoveUnits ScreenMoveUnits;
};
