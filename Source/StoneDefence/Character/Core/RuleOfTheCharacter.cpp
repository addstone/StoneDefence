// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleOfTheCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ARuleOfTheCharacter::ARuleOfTheCharacter()
	:bAttack(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HomePoint = CreateDefaultSubobject<USceneComponent>(TEXT("HomePoint"));
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	OpenFriePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("OpenFilePoint"));
	TraceShowCharacterInformation = CreateDefaultSubobject<UBoxComponent>(TEXT("TraceShowCharacterInformation"));

	HomePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Widget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OpenFriePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TraceShowCharacterInformation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//ÉèÖÃÔ¤ÉèScanning
	TraceShowCharacterInformation->SetCollisionProfileName("Scanning");
	TraceShowCharacterInformation->SetBoxExtent(FVector(38.f, 38.f, 100.f));
}

// Called when the game starts or when spawned
void ARuleOfTheCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ARuleOfTheCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.f;
}

bool ARuleOfTheCharacter::IsDeath()
{
	return false;
}

float ARuleOfTheCharacter::GetHealth()
{
	return 0.f;
}

float ARuleOfTheCharacter::GetMaxHealth()
{
	return 0.f;
}

bool ARuleOfTheCharacter::IsTeam()
{
	return false;
}

EGameCharacterType::Type ARuleOfTheCharacter::GetCharacterType()
{
	return EGameCharacterType::Type::MAX;
}
