// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefencePlayerController.h"
#include "TowerDefenceGameCamera.h"

ATowersDefencePlayerController::ATowersDefencePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ATowersDefencePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	float ScreenSpeed = 20.f;
	ScreenMoveUnits.ListenScreenMove(this, ScreenSpeed);
}

void ATowersDefencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputModeGameAndUI();
}

void ATowersDefencePlayerController::SetInputModeGameAndUI()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);

	SetInputMode(InputMode);
}

void ATowersDefencePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ATowersDefencePlayerController::MouseWheelUP);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ATowersDefencePlayerController::MouseWheelDown);

	InputComponent->BindAction("MouseMiddleButton", IE_Pressed, this, &ATowersDefencePlayerController::MouseMiddleButtonPressed);
	InputComponent->BindAction("MouseMiddleButton", IE_Released, this, &ATowersDefencePlayerController::MouseMiddleButtonReleased);
}

static float WheelValue = 15.f;
void ATowersDefencePlayerController::MouseWheelUP()
{
	ATowerDefenceGameCamera *ZoomCamera = Cast<ATowerDefenceGameCamera>(GetPawn());
	if (ZoomCamera)
	{
		ZoomCamera->Zoom(true, WheelValue);
	}
}

void ATowersDefencePlayerController::MouseWheelDown()
{
	ATowerDefenceGameCamera *ZoomCamera = Cast<ATowerDefenceGameCamera>(GetPawn());
	if (ZoomCamera)
	{
		ZoomCamera->Zoom(false, WheelValue);
	}
}

void ATowersDefencePlayerController::MouseMiddleButtonPressed()
{
	EventMouseMiddlePressed.ExecuteIfBound();
}

void ATowersDefencePlayerController::MouseMiddleButtonReleased()
{
	EventFMouseMiddleReleased.ExecuteIfBound();
}
