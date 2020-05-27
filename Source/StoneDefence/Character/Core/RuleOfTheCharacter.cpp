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
	: DelayDeath(10.f)
	, bAttack(false)

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
	
	TraceShowCharacterInformation->OnClicked.AddDynamic(this, &ARuleOfTheCharacter::OnClicked);

	//生成角色需要生成一个默认的控制
	if (!GetController())
	{
		SpawnDefaultController();
	}


}

void ARuleOfTheCharacter::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	//SD_print_s("Hello");
}

void ARuleOfTheCharacter::UpdateUI()
{
	if (Widget)
	{
		//if (const FCharacterData &InCharacterData = GetCharacterData())
		//{
			if (GetCharacterData().IsValid())
			{
				if (UUI_Health *HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
				{
					HealthUI->SetTitle(GetCharacterData().Name.ToString());
					HealthUI->SetHealth(GetHealth() / GetMaxHealth());
				}
			}
		}
	//}
}

// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateUI();
}

float ARuleOfTheCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	auto DrawGameText = [&](ARuleOfTheCharacter* InOwner, const TCHAR* InText, float InDamageValue, FLinearColor InColor)
	{
		if (DrawTextClass)
		{
			if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass, InOwner->GetActorLocation(), FRotator::ZeroRotator))
			{
				FString DamageText = FString::Printf(InText, InDamageValue);
				MyValueText->SetTextBlock(DamageText, InColor, InDamageValue / InOwner->GetCharacterData().MaxHealth);
			}
		}
	};

	float DamageValue = Expression::GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);

	GetCharacterData().Health -= DamageValue;
	if (!IsActive())
	{

		//奖赏机制
		if (GetGameState()->GetPlayerData().bTeam != IsTeam())
		{
			GetGameState()->GetPlayerData().GameGold += GetCharacterData().Glod;
		}

		GetCharacterData().Health = 0.0f;
		SetLifeSpan(10.f);

		Widget->SetVisibility(false);

		//谁杀死我 谁就得到我提供的最多经验
		if (ARuleOfTheCharacter *CauserCharacter = Cast<ARuleOfTheCharacter>(DamageCauser))
		{
			if (CauserCharacter->IsActive())
			{
				if (CauserCharacter->GetCharacterData().UpdateEP(GetCharacterData().AddEmpiricalValue))
				{

				}

				DrawGameText(CauserCharacter, TEXT("+EP %0.f"), GetCharacterData().AddEmpiricalValue, FLinearColor::Yellow);
			}

			//寻找范围内最近的敌人 升级
			TArray<ARuleOfTheCharacter*> EnemyCharacters;
			StoneDefenceUtils::FindRangeTargetRecently(this, 1000.f, EnemyCharacters);
			for (ARuleOfTheCharacter* InEnemy : EnemyCharacters)
			{
				if (InEnemy != CauserCharacter)
				{
					if (InEnemy->IsActive())
					{
						if (InEnemy->GetCharacterData().UpdateEP(GetCharacterData().AddEmpiricalValue) * 0.3)
						{

						}

						DrawGameText(InEnemy, TEXT("+EP %0.f"), GetCharacterData().AddEmpiricalValue * 0.3, FLinearColor::Yellow);
					}
				}
			}
		}

		GetGameState()->RemoveCharacterData(GUID);
	}

	DrawGameText(this, TEXT("-%0.f"), DamageValue, FLinearColor::Red);

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
	return GetGameState()->GetCharacterData(GUID);
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
			Transform = NewSkeletalMeshComponent->GetComponentTransform();
			NewSkeletalMeshComponent->SetRelativeTransform(FTransform::Identity);
			NewSkeletalMeshComponent->SetWorldTransform(FTransform::Identity);
			NewSkeletalMeshComponent->SetRelativeRotation(Transform.GetRotation());

			if (UStaticMesh *NewMesh = MeshUtils::SkeletalMeshComponentToStaticMesh(NewSkeletalMeshComponent))
			{
				
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
