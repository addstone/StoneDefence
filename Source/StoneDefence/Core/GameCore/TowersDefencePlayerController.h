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
	//按下鼠标的代理
	FSimpleDelegate EventMouseMiddlePressed;
	//松开鼠标的代理
	FSimpleDelegate EventFMouseMiddleReleased;

public:
	ATowersDefencePlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetInputModeGameAndUI();

	virtual void SetupInputComponent() override;
	void MouseWheelUP();
	void MouseWheelDown();

	//鼠标中键控制
	void MouseMiddleButtonPressed();
	void MouseMiddleButtonReleased();

	const FHitResult &GetHitResult();

protected:
	FScreenMoveUnits ScreenMoveUnits;

	FHitResult MouseTaceHit;
};
