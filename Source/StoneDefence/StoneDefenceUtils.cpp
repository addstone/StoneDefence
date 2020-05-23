#include "StoneDefenceUtils.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Interface/Character/RuleCharacter.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/TypeData/ParticleModuleTypeDataMesh.h"
#include "RawMesh.h"

ARuleOfTheCharacter * StoneDefenceUtils::FindTargetRecently(const TArray<ARuleOfTheCharacter*> &InCharacters, const FVector &Loc)
{
	if (InCharacters.Num())
	{
		float TargetDistance = 99999999;
		int32 Index = INDEX_NONE;

		for (int32 i = 0; i < InCharacters.Num(); i++)
		{
			if (ARuleOfTheCharacter* TowerCharacter = InCharacters[i])
			{
				FVector Location = TowerCharacter->GetActorLocation();
				FVector TmpVector = Location - Loc;
				float Distance = TmpVector.Size();

				if (Distance < TargetDistance && TowerCharacter->IsActive())
				{
					Index = i;
					TargetDistance = Distance;
				}
			}
		}

		if (Index != INDEX_NONE)
		{
			return InCharacters[Index];
		}
	}

	return NULL;
}

float Expression::GetDamage(IRuleCharacter *Enemy, IRuleCharacter *Owner)
{
	if (Enemy && Owner)
	{
		//if (FCharacterData *CharacterData = Owner->GetCharacterData())
		//{
		//	if (FCharacterData *EnemyCharacterData = Enemy->GetCharacterData())
		//	{
				return Enemy->GetCharacterData().PhysicalAttack / ((Owner->GetCharacterData().Armor / 100.f) + 1.f);
			}
	//	}
	//}

	return 0.0f;
}

UStaticMesh * MeshUtils::ParticleSystemCompnentToStaticMesh(UParticleSystemComponent *NewParticleSystemComponent)
{
	UStaticMesh *NewStaticMesh = nullptr;
	//if (NewParticleSystemComponent->Template && NewParticleSystemComponent->Template->Emitters.Num() > 0)
	//{
	//	for (const UParticleEmitter *Tmp : NewParticleSystemComponent->Template->Emitters)
	//	{
	//		if (Tmp->LODLevels[0]->bEnabled)
	//		{
	//			if (UParticleModuleTypeDataMesh* MyParticleDataMesh = Cast<UParticleModuleTypeDataMesh>(Tmp->LODLevels[0]->TypeDataModule))
	//			{
	//				if (MyParticleDataMesh->Mesh)
	//				{
	//					NewStaticMesh = MyParticleDataMesh->Mesh;
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}

	return NewStaticMesh;
}

UStaticMesh * MeshUtils::SkeletalMeshComponentToStaticMesh(USkeletalMeshComponent *SkeletalMeshComponent)
{
	UStaticMesh* StaticMesh = nullptr;

	const FTransform& InRootTransform = FTransform::Identity;
	FString MeshName = FGuid::NewGuid().ToString();
	StaticMesh = NewObject<UStaticMesh>(nullptr, *MeshName, RF_Transient);
	StaticMesh->InitResources();

	TArray<FRawMesh> RawMeshes;
	struct FMeshTracker
	{
		FMeshTracker()
			:bValidColors(false)
		{
			FMemory::Memset(bValidTexCoords, 0);
		}

		bool bValidTexCoords;
		bool bValidColors;
	};


	return StaticMesh;
}
