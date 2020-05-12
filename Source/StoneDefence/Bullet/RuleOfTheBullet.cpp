// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleOfTheBullet.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Character/Core/RuleOfTheCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "EngineUtils.h"
#include "../Character/Core/RuleOfTheAIController.h"

// Sets default values
ARuleOfTheBullet::ARuleOfTheBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ParticleMesh = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BulletParticleMesh"));
	BoxDamage = CreateDefaultSubobject<USphereComponent>(TEXT("BulletNoxDamage"));
	RootBullet = CreateDefaultSubobject<USceneComponent>(TEXT("BulletRootBullet"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletProjectileMovement"));

	RootComponent = RootBullet;
	BoxDamage->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//ParticleMesh->AttachToComponent(BoxDamage, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->InitialSpeed = 1600.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->UpdatedComponent = BoxDamage;//加上此句话，子弹卡主，第四章，第三节，19:00//解决方案：将staticmesh作为boxdamage子物体
	BulletType = EBulletType::BULLET_DIRECT_LINE;

	InitialLifeSpan = 4.0f;
}

// Called when the game starts or when spawned
void ARuleOfTheBullet::BeginPlay()
{
	Super::BeginPlay();

	switch (BulletType)
	{
	case EBulletType::BULLET_DIRECT_LINE:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
		break;
	case EBulletType::BULLET_LINE:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
		break;
	case EBulletType::BULLET_TRACK_LINE:
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
		ProjectileMovement->bIsHomingProjectile = true;
		ProjectileMovement->bRotationFollowsVelocity = true;

		if (ARuleOfTheCharacter * InstigatorCharacter = Cast<ARuleOfTheCharacter>(Instigator))
		{
			if (ARuleOfTheAIController *InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
			{
				if (ARuleOfTheCharacter *TargetCharacter = InstigatorController->Target.Get())
				{
					ProjectileMovement->HomingAccelerationMagnitude = 4000.f;
					ProjectileMovement->HomingTargetComponent = TargetCharacter->GetHommingPoint();
				}
			}
		}
	}
		break;
	case EBulletType::BULLET_TRACK_LINE_SP:
		break;
	case EBulletType::BULLET_CHAIN:
		ProjectileMovement->StopMovementImmediately();
		BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case EBulletType::BULLET_RANGE:
		ProjectileMovement->StopMovementImmediately();
		break;
	}

	BoxDamage->OnComponentBeginOverlap.AddUniqueDynamic(this, &ARuleOfTheBullet::BeginOverlap);
}

void ARuleOfTheBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (ARuleOfTheCharacter * InstigatorCharacter = Cast<ARuleOfTheCharacter>(Instigator))
	{
		if (ARuleOfTheCharacter * OtherCharacter = Cast<ARuleOfTheCharacter>(OtherActor)) 
		{
			if (InstigatorCharacter->IsTeam() != OtherCharacter->IsTeam())
			{
				if (OtherCharacter->IsActive())
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamgageParticle, SweepResult.Location);
					UGameplayStatics::ApplyDamage(OtherCharacter, 100.f, InstigatorCharacter->GetController(), InstigatorCharacter, UDamageType::StaticClass());
				}

				switch (BulletType)
				{
				case EBulletType::BULLET_LINE:
				case EBulletType::BULLET_TRACK_LINE:
					Destroy();
					break;
				}
			}
		}
	}


}

// Called every frame
void ARuleOfTheBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

