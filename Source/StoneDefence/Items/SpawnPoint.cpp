// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "../StoneDefenceType.h"

ASpawnPoint::ASpawnPoint()
{
	Team = ETeam::BLUE;
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}
