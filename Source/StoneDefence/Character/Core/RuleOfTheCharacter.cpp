// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleOfTheCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "../../UI/Character/UI_Health.h"
#include "../../Data/CharacterData.h"
#include "../../StoneDefenceUtils.h"
#include "../../SimpleDrawText/Source/SimpleDrawText/Public/Actor/DrawText.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/TypeData/ParticleModuleTypeDataMesh.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleLODLevel.h"
#include "../../StoneDefenceMacro.h"

// Sets default values
ARuleOfTheCharacter::ARuleOfTheCharacter()
	:bAttack(false)
{
	GUID = FGuid::NewGuid();
	//SD_print_r(Error, "The xxxxxxxxcurrent [%i] is invalid", *GUID.ToString());
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

	//设置预设Scanning
	TraceShowCharacterInformation->SetCollisionProfileName("Scanning");
	TraceShowCharacterInformation->SetBoxExtent(FVector(38.f, 38.f, 100.f));

}

// Called when the game starts or when spawned
void ARuleOfTheCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//生成角色需要生成一个默认的控制
	if (!GetController())
	{
		SpawnDefaultController();
	}

	UpdateUI();
}

void ARuleOfTheCharacter::UpdateUI()
{
	if (Widget)
	{
		//if (const FCharacterData *InCharacterData = GetCharacterData())
		//{
		//	if (InCharacterData->IsValid())
		//	{
				if (UUI_Health *HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
				{
					HealthUI->SetTitle(GetCharacterData().Name.ToString());
					HealthUI->SetHealth(GetHealth() / GetMaxHealth());
				}
			}
	//	}
	//}
}

// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ARuleOfTheCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	float DamageValue = Expression::GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);

	GetCharacterData().Health -= DamageValue;
	if (!IsActive())
	{
		GetCharacterData().Health = 0.0f;
	}

	UpdateUI();

	if (DrawTextClass)
	{
		if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass, GetActorLocation(), FRotator::ZeroRotator))
		{
			FString DamageText = FString::Printf(TEXT("-%0.f"), DamageValue);
			MyValueText->SetTextBlock(DamageText, FLinearColor::Red, DamageValue / GetCharacterData().MaxHealth);
		}
	}
	return DamageValue;
}

bool ARuleOfTheCharacter::IsDeath()
{
	
	return GetHealth() <= 0.f;
}

float ARuleOfTheCharacter::GetHealth()
{
	return GetCharacterData().Health;
}

float ARuleOfTheCharacter::GetMaxHealth()
{
	return GetCharacterData().MaxHealth;
}

bool ARuleOfTheCharacter::IsTeam()
{
	return false;
}

FCharacterData & ARuleOfTheCharacter::GetCharacterData()
{
	if (GetGameState())
	{
		return GetGameState()->GetCharacterData(GUID);
	}
	return CharacterDataNULL;
}

UStaticMesh * ARuleOfTheCharacter::GetDollMesh(FTransform &Transform, int32 MeshID)
{
	TArray<USceneComponent*> SceneComponent;
	RootComponent->GetChildrenComponents(true, SceneComponent);
	for (auto &Tmp : SceneComponent)
	{
		if (UStaticMeshComponent *NewMeshComponent = Cast<UStaticMeshComponent>(Tmp))
		{
			if (NewMeshComponent->GetStaticMesh())
			{
				Transform = NewMeshComponent->GetComponentTransform();
				return NewMeshComponent->GetStaticMesh();
			}
		}
		else if (UParticleSystemComponent *NewParticleSystemComponent = Cast<UParticleSystemComponent>(Tmp))
		{
			if (NewParticleSystemComponent->Template && NewParticleSystemComponent->Template->Emitters.Num() > 0)
			{
				for (const UParticleEmitter *Tmp_ : NewParticleSystemComponent->Template->Emitters)
				{
					if (Tmp_->LODLevels[0]->bEnabled)
					{
						if (UParticleModuleTypeDataMesh* MyParticleDataMesh = Cast<UParticleModuleTypeDataMesh>(Tmp_->LODLevels[0]->TypeDataModule))
						{
							if (MyParticleDataMesh->Mesh)
							{
								Transform = NewParticleSystemComponent->GetComponentTransform();
								return MyParticleDataMesh->Mesh;
							}
						}
					}
				}
			}
		}
		else if (USkeletalMeshComponent *NewSkeletalMeshComponent = Cast<USkeletalMeshComponent>(Tmp))
		{
			
				if (UStaticMesh *NewMesh = MeshUtils::SkeletalMeshComponentToStaticMesh(NewSkeletalMeshComponent))
				{
					Transform = NewSkeletalMeshComponent->GetComponentTransform();
					return NewMesh;
				}
			
		}
	}

	return NULL;
}

EGameCharacterType::Type ARuleOfTheCharacter::GetCharacterType()
{
	return EGameCharacterType::Type::MAX;
}
