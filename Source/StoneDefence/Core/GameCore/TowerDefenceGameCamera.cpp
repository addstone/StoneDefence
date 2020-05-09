// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenceGameCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATowerDefenceGameCamera::ATowerDefenceGameCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main_Camera"));
	MarkBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Sign"));

	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MainCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	MarkBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CameraBoom->TargetArmLength = 799.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	MarkBox->SetCollisionProfileName(TEXT("ControllerPawnProfile"));
}

// Called when the game starts or when spawned
void ATowerDefenceGameCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATowerDefenceGameCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//void ATowerDefenceGameCamera::Zoom(bool bDirection, float ZoomSpeed)
//{
//	float MiniTargetArmLength = GLOBAL_MANAGEMENT_MACRO()->GetGlobalConfiguration()->MiniTargetArmLength;
//	float MaxTargetArmLength = GLOBAL_MANAGEMENT_MACRO()->GetGlobalConfiguration()->MaxTargetArmLength;
//
//	if (bDirection)
//	{
//		if (CameraBoom->TargetArmLength > MiniTargetArmLength)
//		{
//			CameraBoom->TargetArmLength -= ZoomSpeed * 2;
//		}
//	}
//	else
//	{
//		if (CameraBoom->TargetArmLength < MaxTargetArmLength)
//		{
//			CameraBoom->TargetArmLength += ZoomSpeed * 2;
//		}
//	}
//}

//float ATowerDefenceGameCamera::GetTargetArmLength() const
//{
//	return CameraBoom->TargetArmLength;
//}

