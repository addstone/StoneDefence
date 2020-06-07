// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters.h"
#include "../../StoneDefenceMacro.h"
#include "../../Global/UI_Data.h"
#include "GameFramework/CharacterMovementComponent.h"

void AMonsters::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//速度设定
	if (const FCharacterData *InCharacterData = GetCharacterData())
	{
		if (InCharacterData->IsValid())
		{
			GetCharacterMovement()->MaxWalkSpeed = InCharacterData->GetWalkSpeed();
		}
	}
}

void AMonsters::RegisterTeam()
{
	GetCharacterData()->Team = ETeam::BLUE;
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
