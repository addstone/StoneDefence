// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers.h"
#include "Components/StaticMeshComponent.h"
#include "DestructibleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../StoneDefenceMacro.h"
#include "../../Global/UI_Data.h"

ATowers::ATowers()
{
	ParticleMesh = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleMesh"));
	StaticMeshBuilding = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RangeBuilding"));
	DestructibleMeshBuilding = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Subsitute"));

	StaticMeshBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	DestructibleMeshBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATowers::RegisterTeam()
{
	GetCharacterData().Team = ETeam::RED;
}

float ATowers::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.f;
}

void ATowers::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Super::OnClicked(TouchedComponent, ButtonPressed);
	SD_print_s("Tower");

	if (ClickedTargetTower == nullptr)
	{
		ClickedTargetTower = this;
	}
	else
	{
		ClickedTargetTower = nullptr;
	}
}
