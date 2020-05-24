// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters.h"
#include "../../UI/Core/UI_Data.h"
#include "../../StoneDefenceMacro.h"

void AMonsters::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AMonsters::IsTeam()
{
	return Super::IsTeam();
}

EGameCharacterType::Type AMonsters::GetCharacterType()
{
	return EGameCharacterType::Type::MONSTER;
}

void AMonsters::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Super::OnClicked(TouchedComponent, ButtonPressed);
	SD_print_s("Monster");
	if (ClickedTargetMonster)
	{
		ClickedTargetMonster = nullptr;
	}
	else
	{
		ClickedTargetMonster = this;
	}
}
