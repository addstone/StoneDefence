// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerDefenceHallPawn.generated.h"

UCLASS()
class STONEDEFENCE_API ATowerDefenceHallPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HallPawn, meta = (AllowPrivateAccess = "true"))
		class USceneComponent *NewRoot;
public:
	// Sets default values for this pawn's properties
	ATowerDefenceHallPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
