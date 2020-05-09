// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefencePlayerController.h"

ATowersDefencePlayerController::ATowersDefencePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ATowersDefencePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATowersDefencePlayerController::BeginPlay()
{
	Super::BeginPlay();
}
