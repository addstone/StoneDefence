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
#include "Math/UnrealMathUtility.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"
#include "../StoneDefenceUtils.h"

// Sets default values
ARuleOfTheBullet::ARuleOfTheBullet()
{
	SplineOffset = 0.0f;
	CurrentSplineTime = 0.f;
	ChainAttackCount = 3;
	Spline = nullptr;
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

	if (ARuleOfTheCharacter * InstigatorCharacter = Cast<ARuleOfTheCharacter>(Instigator))
	{
		if (ARuleOfTheAIController *InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter *TargetCharacter = InstigatorController->Target.Get())
			{

				switch (BulletType)
				{
				case EBulletType::BULLET_DIRECT_LINE:
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					break;
				case EBulletType::BULLET_LINE:
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					break;
				case EBulletType::BULLET_TRACK_LINE://use spline
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					ProjectileMovement->bIsHomingProjectile = true;
					ProjectileMovement->bRotationFollowsVelocity = true;

					ProjectileMovement->HomingAccelerationMagnitude = 4000.f;
					ProjectileMovement->HomingTargetComponent = TargetCharacter->GetHommingPoint();
					break;
				}
				case EBulletType::BULLET_TRACK_LINE_SP:
				{
					ProjectileMovement->StopMovementImmediately();
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());

					Spline = NewObject<USplineComponent>(this, TEXT("SplineInstance"));
					Spline->RegisterComponent();

					Spline->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::Local);
					FVector DistanceVector = InstigatorCharacter->GetActorLocation() - TargetCharacter->GetActorLocation();
					FVector Position = (DistanceVector / 2) + TargetCharacter->GetActorLocation();
					Position.Y += SplineOffset;
					Position.Z = (DistanceVector.Size() / 2.f) * 0.5f;
					Spline->SetLocationAtSplinePoint(1, Position, ESplineCoordinateSpace::Local);
					Spline->AddSplinePoint(TargetCharacter->GetActorLocation(), ESplineCoordinateSpace::Local);

					break;
				}
				case EBulletType::BULLET_CHAIN:
				{
					ProjectileMovement->StopMovementImmediately();
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					UGameplayStatics::SpawnEmitterAttached(DamgageParticle, TargetCharacter->GetHommingPoint());

					GetWorld()->GetTimerManager().SetTimer(ChainAttackHandle, this, &ARuleOfTheBullet::ChainAttack, 0.1f);

					//SubmissionSkillRequest();
					break;
				}
				case EBulletType::BULLET_RANGE_LINE:
				{
					ProjectileMovement->StopMovementImmediately();

					ProjectileMovement->ProjectileGravityScale = 1.f;
					FVector TargetFormOwnerVector = TargetCharacter->GetActorLocation() - GetActorLocation();

					float InTime = (TargetFormOwnerVector.Size() / ProjectileMovement->InitialSpeed);
					float Y = ProjectileMovement->GetGravityZ() * InTime;
					float X = ProjectileMovement->InitialSpeed * InTime;
					float V = FMath::Sqrt(X * X + Y * Y);

					float CosRadian = FMath::Acos(TargetFormOwnerVector.Size() / V * (InTime * (PI * 0.1f)));
					FRotator Rot = GetActorRotation();
					Rot.Pitch = CosRadian * (180 / PI);
					SetActorRotation(Rot);

					ProjectileMovement->SetVelocityInLocalSpace(FVector(1.0f, 0.f, 0.f) * ProjectileMovement->InitialSpeed);

				}
				break;
				case EBulletType::BULLET_RANGE:
					ProjectileMovement->StopMovementImmediately();
					ProjectileMovement->SetVelocityInLocalSpace(FVector(1.0f, 0.f, 0.f) * ProjectileMovement->InitialSpeed);//没有这句话，子弹会没有初速度而不动
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					RadialDamage(GetActorLocation(), Cast<ARuleOfTheCharacter>(Instigator));
					break;;
				}
			}
		}
	}
	BoxDamage->OnComponentBeginOverlap.AddUniqueDynamic(this, &ARuleOfTheBullet::BeginOverlap);
}

void ARuleOfTheBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (ARuleOfTheCharacter * InstigatorCharacter = Cast<ARuleOfTheCharacter>(Instigator))
	{
		if (ARuleOfTheCharacter * OtherCharacter = Cast<ARuleOfTheCharacter>(OtherActor)) 
		{
			if (InstigatorCharacter->GetTeamType() != OtherCharacter->GetTeamType())
			{
				if (OtherCharacter->IsActive())
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamgageParticle, SweepResult.Location);
					
					float DamageValue = Expression::GetDamage(InstigatorCharacter, OtherCharacter);

					switch (BulletType)
					{
					case EBulletType::BULLET_DIRECT_LINE:
					case EBulletType::BULLET_LINE:
					case EBulletType::BULLET_TRACK_LINE:
					case EBulletType::BULLET_TRACK_LINE_SP:
						UGameplayStatics::ApplyDamage(
							OtherCharacter, 
							DamageValue,
							InstigatorCharacter->GetController(), 
							InstigatorCharacter, 
							UDamageType::StaticClass());

						Destroy();
						break;
					case EBulletType::BULLET_RANGE_LINE:
						RadialDamage(OtherCharacter->GetActorLocation(), InstigatorCharacter);
						Destroy();
						break;
					//case EBulletType::BULLET_RANGE:
					//	break;
					}
				}


			}
		}
	}
}

void ARuleOfTheBullet::RadialDamage(const FVector& Origin, ARuleOfTheCharacter * InstigatorCharacter)
{
	if (InstigatorCharacter)
	{
		TArray<AActor*> IgnoreActors;
		//TArray<ARuleOfTheCharacter*> TargetActors;
		for (TActorIterator<ARuleOfTheCharacter>it(GetWorld(), ARuleOfTheCharacter::StaticClass()); it; ++it)
		{
			if (ARuleOfTheCharacter *TheCharacter = *it)
			{
				FVector VDistance = TheCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
				if (VDistance.Size() <= 1400)
				{
					if (TheCharacter->GetTeamType() == InstigatorCharacter->GetTeamType())
					{
						IgnoreActors.Add(TheCharacter);
					}
					else
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamgageParticle, TheCharacter->GetActorLocation());
						//TargetActors.Add(TheCharacter);
					}
				}
			}
		}
		UGameplayStatics::ApplyRadialDamageWithFalloff(
			GetWorld(), 
			100.f, 10.f,
			Origin, 
			400.f, 
			1000.f, 
			1.f, 
			UDamageType::StaticClass(), 
			IgnoreActors, 
			Instigator,
			Instigator->GetController(),
			ECollisionChannel::ECC_MAX);
	}
}

void ARuleOfTheBullet::ChainAttack()
{
	if (ChainAttackHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ChainAttackHandle);
	}

	//主要伤害区
	if (ARuleOfTheCharacter * InstigatorCharacter = Cast<ARuleOfTheCharacter>(Instigator))
	{
		if (ARuleOfTheAIController *InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter *TargetCharacter = InstigatorController->Target.Get())
			{
				UGameplayStatics::SpawnEmitterAttached(DamgageParticle, TargetCharacter->GetHommingPoint());
				UGameplayStatics::SpawnEmitterAttached(OpenFireParticle, InstigatorCharacter->GetHommingPoint());


				UGameplayStatics::ApplyDamage(
					TargetCharacter,
					100.f,
					InstigatorCharacter->GetController(),
					InstigatorCharacter,
					UDamageType::StaticClass());
			}
		}
	}

	ChainAttackCount--;
	if (ChainAttackCount > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(ChainAttackHandle, this, &ARuleOfTheBullet::ChainAttack, 0.3f);
	}
}

// Called every frame
void ARuleOfTheBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ARuleOfTheCharacter * InstigatorCharacter = Cast<ARuleOfTheCharacter>(Instigator))//GetInstigator<ARuleOfTheCharacter>()
	{
		if (ARuleOfTheAIController *InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter *TargetCharacter = InstigatorController->Target.Get())
			{
				switch (BulletType)
				{
					case EBulletType::BULLET_CHAIN:
					{
						TArray<USceneComponent*> SceneComponent;
						RootComponent->GetChildrenComponents(true, SceneComponent);
						for (auto & Tmp : SceneComponent)
						{
							if (UParticleSystemComponent *ParticleSystem = Cast<UParticleSystemComponent>(Tmp))
							{
								ParticleSystem->SetBeamSourcePoint(0, InstigatorCharacter->GetFirePoint()->GetComponentLocation(), 0);
								ParticleSystem->SetBeamTargetPoint(0, TargetCharacter->GetHommingPoint()->GetComponentLocation(), 0);
							}
						}
						break;
					}
					case EBulletType::BULLET_TRACK_LINE_SP:
					{
						//Bug  空白处生成多余的爆炸
						if (Spline)
						{
							FVector DistanceVector = TargetCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
							CurrentSplineTime += DeltaTime;

							float Distance = Spline->GetSplineLength() * (CurrentSplineTime / (DistanceVector.Size() / 1000.f));
							FVector Loction = Spline->GetWorldLocationAtDistanceAlongSpline(Distance);
							FRotator Rotator = Spline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

							SetActorLocationAndRotation(Loction, Rotator);

							if ((Loction - TargetCharacter->GetActorLocation()).Size() <= 100.f)
							{
								FHitResult SweepResult;
								SweepResult.Location = Loction;

								//为什么手动激活？
								BeginOverlap(nullptr, TargetCharacter, nullptr, 0, false, SweepResult);
							}
						}
						break;
					}
				}
				if (!TargetCharacter->IsActive())
				{
					Destroy();
				}
			}
			else
			{
				Destroy();
			}
		}
	}
}

