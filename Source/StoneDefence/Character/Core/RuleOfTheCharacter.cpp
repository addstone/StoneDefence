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
#include "../../Bullet/RuleOfTheBullet.h"
#include "../Damage/RuleOfTheDamage.h"
#include "../../Global/RuleOfTheGlobal.h"

// Sets default values
ARuleOfTheCharacter::ARuleOfTheCharacter()
	: DelayDeath(10.f)
	, bAttack(false)

{
	GUID = FGuid::NewGuid();
	CharacterType = EGameCharacterType::MINI;
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

void ARuleOfTheCharacter::ResetGUID()
{
	GUID = FGuid::NewGuid();
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
		if (const FCharacterData *InCharacterData = GetCharacterData())
		{
			if (InCharacterData->IsValid())
			{
				if (UUI_Health *HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
				{
					HealthUI->SetTitle(InCharacterData->Name.ToString());
					HealthUI->SetHealth(GetHealth() / GetMaxHealth());
				}
			}
		}
	}
}

void ARuleOfTheCharacter::UpdateSkill(int32 SkillID)
{
	for (auto &Tmp : SkillIDs)
	{
		if (Tmp == SkillID)
		{
			if (ARuleOfTheBullet *Bullet = StoneDefenceUtils::SpawnBullet(GetWorld(), this, Tmp, OpenFriePoint->GetComponentLocation(), OpenFriePoint->GetComponentRotation()))
			{
				Bullet->InitSkill();
			}
			break;
		}
	}
}

void ARuleOfTheCharacter::InitSkill()
{
	for (auto &Tmp : SkillIDs)
	{
		if (ARuleOfTheBullet *Bullet = StoneDefenceUtils::SpawnBullet(GetWorld(), this, Tmp, OpenFriePoint->GetComponentLocation(), OpenFriePoint->GetComponentRotation()))
		{
			Bullet->InitSkill();
		}
	}
}

void ARuleOfTheCharacter::SubmissionSkillRequest(int32 SkillID)
{
	if (!GetGameState()->IsVerificationSkill(GUID, SkillID))
	{
		GetGameState()->AddSkill(GUID, SkillID);
	}
}

void ARuleOfTheCharacter::RemoveSkillSlot_Client(const FGuid &SlotID)
{
	if (UUI_Health *HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
	{
		HealthUI->RemoveSkillSlot(SlotID);
	}
}

void ARuleOfTheCharacter::AddSkillSlot_Client(const FGuid &SlotID)
{
	if (UUI_Health *HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
	{
		HealthUI->AddSkillSlot(SlotID);
	}
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

	float DamageValue = 0.f;

	if (FCharacterData *InCharacterData = GetCharacterData())
	{
		if (URuleOfTheDamage *DamageClass = DamageEvent.DamageTypeClass->GetDefaultObject<URuleOfTheDamage>())
		{
			if (const FSkillData *SkillData = DamageClass->SkillData)
			{
				auto DrawGameText = [&](ARuleOfTheCharacter* InOwner, const TCHAR* InText, float InDamageValue, FLinearColor InColor)
				{
					if (DrawTextClass)
					{
						if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass, InOwner->GetActorLocation(), FRotator::ZeroRotator))
						{
							FString DamageText = FString::Printf(InText, InDamageValue);
							MyValueText->SetTextBlock(DamageText, InColor, InDamageValue / InOwner->GetCharacterData()->GetMaxHealth());
						}
					}
				};
				if (SkillData->SkillType.SkillEffectType == ESkillEffectType::SUBTRACT)
				{
					DamageValue = Expression::GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);
					if (DamageValue)
					{
						InCharacterData->Health -= DamageValue;
						//绘制受伤字体
						DrawGameText(this, TEXT("-%0.f"), DamageValue, FLinearColor::Red);
					}

					if (SkillData->AttackSpeed)
					{
						InCharacterData->AttackSpeed -= SkillData->AttackSpeed;
						//绘制受伤字体
						DrawGameText(this, TEXT("-%0.f"), SkillData->AttackSpeed, FLinearColor::Black);
					}
					if (SkillData->PhysicalAttack)
					{
						InCharacterData->PhysicalAttack -= SkillData->PhysicalAttack;
						//绘制受伤字体
						DrawGameText(this, TEXT("-%0.f"), SkillData->PhysicalAttack, FLinearColor::Black);
					}
					if (SkillData->Armor)
					{
						InCharacterData->Armor -= SkillData->Armor;
						//绘制受伤字体
						DrawGameText(this, TEXT("-%0.f"), SkillData->Armor, FLinearColor::Black);
					}
				}
				else if (SkillData->SkillType.SkillEffectType == ESkillEffectType::ADD)
				{
					if (SkillData->PhysicalAttack)
					{
						InCharacterData->PhysicalAttack += SkillData->PhysicalAttack;
						//绘制受伤字体
						DrawGameText(this, TEXT("+%0.f"), SkillData->PhysicalAttack, FLinearColor::Blue);
					}

					if (SkillData->Armor)
					{
						InCharacterData->Armor += SkillData->Armor;
						//绘制受伤字体
						DrawGameText(this, TEXT("+%0.f"), SkillData->Armor, FLinearColor::White);
					}

					if (SkillData->AttackSpeed)
					{
						InCharacterData->AttackSpeed += SkillData->AttackSpeed;
						//绘制受伤字体
						DrawGameText(this, TEXT("+%0.f"), SkillData->AttackSpeed, FLinearColor::White);
					}

					if (SkillData->Health)
					{
						InCharacterData->Health += SkillData->Health;
						if (InCharacterData->Health > InCharacterData->MaxHealth)
						{
							InCharacterData->Health = InCharacterData->MaxHealth;
						}

						//绘制受伤字体
						DrawGameText(this, TEXT("+%0.f"), SkillData->Health, FLinearColor::Green);
					}
				}

				//死亡判定
				if (!IsActive())
				{
					CharacterDeath();
					//奖赏机制
					if (GetPlayerState()->GetPlayerData().Team != GetTeamType())
					{
						GetPlayerState()->GetPlayerData().GameGold += InCharacterData->Glod;
					}

					GetCharacterData()->Health = 0.0f;
					SetLifeSpan(10.f);

					Widget->SetVisibility(false);

					//谁杀死我 谁就得到我提供的最多经验
					if (ARuleOfTheCharacter *CauserCharacter = Cast<ARuleOfTheCharacter>(DamageCauser))
					{
						if (CauserCharacter->IsActive())
						{
							if (CauserCharacter->GetCharacterData()->UpdateEP(InCharacterData->AddEmpiricalValue))
							{

							}

							DrawGameText(CauserCharacter, TEXT("+EP %0.f"), InCharacterData->AddEmpiricalValue, FLinearColor::Yellow);
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
									if (InEnemy->GetCharacterData()->UpdateEP(InCharacterData->AddEmpiricalValue) * 0.3)
									{

									}

									DrawGameText(InEnemy, TEXT("+EP %0.f"), InCharacterData->AddEmpiricalValue * 0.3, FLinearColor::Yellow);
								}
							}
						}
					}

					GetGameState()->RemoveCharacterData(GUID);
				}
				else
				{
					SubmissionSkillRequest(SkillData->ID);
				}

			}
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
	if (FCharacterData *InCharacterData = GetCharacterData())
	{
		return InCharacterData->Health;
	}
	return 0.f;
}

float ARuleOfTheCharacter::GetMaxHealth()
{
	if (FCharacterData *InCharacterData = GetCharacterData())
	{
		return InCharacterData->GetMaxHealth();
	}

	return 100.f;
}

ETeam ARuleOfTheCharacter::GetTeamType()
{
	if (FCharacterData *InCharacterData = GetCharacterData())
	{
		return InCharacterData->Team;
	}

	return ETeam::MAX;
}

FCharacterData * ARuleOfTheCharacter::GetCharacterData()
{
	if (GetGameState())
	{
		return GetGameState()->GetCharacterData(GUID);
	}

	return nullptr;
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
			if (UStaticMesh *NewMesh = MeshUtils::ParticleSystemCompnentToStaticMesh(NewParticleSystemComponent))
			{
				Transform = NewParticleSystemComponent->GetComponentTransform();
				return NewMesh;
			}
		}
		else if (USkeletalMeshComponent *NewSkeletalMeshComponent = Cast<USkeletalMeshComponent>(Tmp))
		{
			Transform = NewSkeletalMeshComponent->GetComponentTransform();
			NewSkeletalMeshComponent->SetRelativeTransform(FTransform::Identity);
			NewSkeletalMeshComponent->SetWorldTransform(FTransform::Identity);
			NewSkeletalMeshComponent->SetRelativeRotation(Transform.GetRotation());

			//if (UStaticMesh *NewMesh = MeshUtils::SkeletalMeshComponentToStaticMesh(NewSkeletalMeshComponent))
			//{

			//	return NewMesh;
			//}

			if (UStaticMesh *InNewMesh = DOLL_MESH_POOL_MANAGE_MACRO()->GetStaticMesh(MeshID))
			{
				return InNewMesh;
			}
			else
			{
				if (UStaticMesh *InNewMesh2 = MeshUtils::SkeletalMeshComponentToStaticMesh(NewSkeletalMeshComponent))
				{
					DOLL_MESH_POOL_MANAGE_MACRO()->Add(MeshID, InNewMesh2);
					return InNewMesh2;
				}
			}
			
		}
	}

	return NULL;
}

EGameCharacterType::Type ARuleOfTheCharacter::GetCharacterType()
{
	return CharacterType;
}
