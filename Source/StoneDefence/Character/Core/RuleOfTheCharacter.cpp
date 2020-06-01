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

	//����Ԥ��Scanning
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

	//���ɽ�ɫ��Ҫ����һ��Ĭ�ϵĿ���
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

	FCharacterData &InCharacterData = GetCharacterData();
	
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
							MyValueText->SetTextBlock(DamageText, InColor, InDamageValue / InOwner->GetCharacterData().GetMaxHealth());
						}
					}
				};
				if (SkillData->SkillType.SkillEffectType == ESkillEffectType::SUBTRACT) 
				{
					DamageValue = Expression::GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);
					if (DamageValue)
					{
						GetCharacterData().Health -= DamageValue;		
						//������������
						DrawGameText(this, TEXT("-%0.f"), DamageValue, FLinearColor::Red);
					}
					if (SkillData->AttackSpeed)
					{
						GetCharacterData().AttackSpeed -= SkillData->AttackSpeed;
						//������������
						DrawGameText(this, TEXT("-%0.f"), SkillData->AttackSpeed, FLinearColor::Black);
					}
					if (SkillData->PhysicalAttack)
					{
						GetCharacterData().PhysicalAttack -= SkillData->PhysicalAttack;
						//������������
						DrawGameText(this, TEXT("-%0.f"), SkillData->PhysicalAttack, FLinearColor::Black);
					}
					if (SkillData->Armor)
					{
						GetCharacterData().Armor -= SkillData->Armor;
						//������������
						DrawGameText(this, TEXT("-%0.f"), SkillData->Armor, FLinearColor::Black);
					}
				}
				else if (SkillData->SkillType.SkillEffectType == ESkillEffectType::ADD)
				{
					if (SkillData->PhysicalAttack)
					{
						GetCharacterData().PhysicalAttack += SkillData->PhysicalAttack;
						//������������
						DrawGameText(this, TEXT("+%0.f"), SkillData->PhysicalAttack, FLinearColor::Blue);
					}

					if (SkillData->Armor)
					{
						GetCharacterData().Armor += SkillData->Armor;
						//������������
						DrawGameText(this, TEXT("+%0.f"), SkillData->Armor, FLinearColor::White);
					}

					if (SkillData->AttackSpeed)
					{
						GetCharacterData().AttackSpeed += SkillData->AttackSpeed;
						//������������
						DrawGameText(this, TEXT("+%0.f"), SkillData->AttackSpeed, FLinearColor::White);
					}

					if (SkillData->Health)
					{
						GetCharacterData().Health += SkillData->Health;
						if (GetCharacterData().Health > GetCharacterData().MaxHealth)
						{
							GetCharacterData().Health = GetCharacterData().MaxHealth;
						}

						//������������
						DrawGameText(this, TEXT("+%0.f"), SkillData->Health, FLinearColor::Green);
					}
				}

				//�����ж�
				if (!IsActive())
				{
					CharacterDeath();
					//���ͻ���
					if (GetPlayerState()->GetPlayerData().Team != GetTeamType())
					{
						GetPlayerState()->GetPlayerData().GameGold += GetCharacterData().Glod;
					}

					GetCharacterData().Health = 0.0f;
					SetLifeSpan(10.f);

					Widget->SetVisibility(false);

					//˭ɱ���� ˭�͵õ����ṩ����ྭ��
					if (ARuleOfTheCharacter *CauserCharacter = Cast<ARuleOfTheCharacter>(DamageCauser))
					{
						if (CauserCharacter->IsActive())
						{
							if (CauserCharacter->GetCharacterData().UpdateEP(GetCharacterData().AddEmpiricalValue))
							{

							}

							DrawGameText(CauserCharacter, TEXT("+EP %0.f"), GetCharacterData().AddEmpiricalValue, FLinearColor::Yellow);
						}

						//Ѱ�ҷ�Χ������ĵ��� ����
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
	return GetCharacterData().GetMaxHealth();
}

ETeam ARuleOfTheCharacter::GetTeamType()
{
	return GetCharacterData().Team;
}

FCharacterData & ARuleOfTheCharacter::GetCharacterData()
{
#if WITH_EDITOR
	if (GetGameState())
	{
		return GetGameState()->GetCharacterData(GUID);
	}
	return NULLData;
#else
	return GetGameState()->GetCharacterData(GUID);
#endif
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
			//if (NewParticleSystemComponent->Template && NewParticleSystemComponent->Template->Emitters.Num() > 0)
			//{
			//	for (const UParticleEmitter *Tmp_ : NewParticleSystemComponent->Template->Emitters)
			//	{
			//		if (Tmp_->LODLevels[0]->bEnabled)
			//		{
			//			if (UParticleModuleTypeDataMesh* MyParticleDataMesh = Cast<UParticleModuleTypeDataMesh>(Tmp_->LODLevels[0]->TypeDataModule))
			//			{
			//				if (MyParticleDataMesh->Mesh)
			//				{
			//					Transform = NewParticleSystemComponent->GetComponentTransform();
			//					return MyParticleDataMesh->Mesh;
			//				}
			//			}
			//		}
			//	}
			//}
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
	return CharacterType;
}
