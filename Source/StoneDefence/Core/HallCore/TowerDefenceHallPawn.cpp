// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceHallPawn.h"
#include "Components/SceneComponent.h"

// Sets default values
ATowerDefenceHallPawn::ATowerDefenceHallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	NewRoot = CreateDefaultSubobject<USceneComponent>(TEXT("NewRoot"));
	RootComponent = NewRoot;

}

// Called when the game starts or when spawned
void ATowerDefenceHallPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerDefenceHallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATowerDefenceHallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

