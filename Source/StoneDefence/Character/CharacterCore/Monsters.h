// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/RuleOfTheCharacter.h"
#include "../../StoneDefenceType.h"
#include "Monsters.generated.h"


/**
 * 
 */
UCLASS()
class STONEDEFENCE_API AMonsters : public ARuleOfTheCharacter
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual ETeam GetTeamType();


protected:
	virtual void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
};
