#include "StoneDefenceUtils.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Interface/Character/RuleCharacter.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/TypeData/ParticleModuleTypeDataMesh.h"
#include "RawMesh.h"
#include "Engine/SkeletalMesh.h"
#include "SkeletalRenderPublic.h"
#include "Components/SkinnedMeshComponent.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Rendering/SkeletalMeshLODRenderData.h"
#include "Math/UnrealMathSSE.h"
#include "RawIndexBuffer.h"

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

struct FMeshTracker
{
	FMeshTracker()
		:bValidColors(false)
	{
		FMemory::Memset(bValidTexCoords, 0);
	}

	bool bValidTexCoords[MAX_MESH_TEXTURE_COORDS];
	bool bValidColors;
};

void SkeletalMeshToRawMeshes(
	USkeletalMeshComponent* InComponent,
	int32 InOverallMaxLODs,
	const FMatrix& InComponentToWorld,
	FMeshTracker &MeshTracker,
	FRawMesh &RawMesh)
{
	FSkeletalMeshLODInfo& SrcLODInfo = *(InComponent->SkeletalMesh->GetLODInfo(InOverallMaxLODs));

	TArray<FFinalSkinVertex> FinalVertices;
	InComponent->GetCPUSkinnedVertices(FinalVertices, InOverallMaxLODs);
	FSkeletalMeshRenderData& SkeletalMeshRenderData = InComponent->MeshObject->GetSkeletalMeshRenderData();
	FSkeletalMeshLODRenderData& LODData = SkeletalMeshRenderData.LODRenderData[InOverallMaxLODs];

	for (int32 VertIndex = 0; VertIndex < FinalVertices.Num(); ++VertIndex)
	{
		RawMesh.VertexPositions.Add(InComponentToWorld.TransformPosition(FinalVertices[VertIndex].Position));
	}

	const uint32 NumTexCoords = FMath::Min(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords(), (uint32)MAX_MESH_TEXTURE_COORDS);
	const int32 NumSections = LODData.RenderSections.Num();

	FRawStaticIndexBuffer16or32Interface& IndexBuffer = *LODData.MultiSizeIndexContainer.GetIndexBuffer();
	for (int32 SectionIndex = 0; SectionIndex < NumSections; SectionIndex++)
	{
		const FSkelMeshRenderSection& SkelMeshSection = LODData.RenderSections[SectionIndex];
		if (InComponent->IsMaterialSectionShown(SkelMeshSection.MaterialIndex, InOverallMaxLODs))
		{
			const int32 NumWedges = SkelMeshSection.NumTriangles * 3;
			for (int32 WedgeIndex = 0; WedgeIndex < NumWedges; WedgeIndex++)
			{
				const int32 VertexIndexForWedge = IndexBuffer.Get(SkelMeshSection.BaseIndex + WedgeIndex);
				RawMesh.WedgeIndices.Add(VertexIndexForWedge);

				const FFinalSkinVertex& SkinnedVertex = FinalVertices[VertexIndexForWedge];
				const FVector TangentX = InComponentToWorld.TransformVector(SkinnedVertex.TangentX.ToFVector());
				const FVector TangentZ = InComponentToWorld.TransformVector(SkinnedVertex.TangentZ.ToFVector());
				const FVector4 UnpackedTangentX = SkinnedVertex.TangentX.ToFVector4();
				const FVector TangentY = (TangentZ ^ TangentX).GetSafeNormal() * UnpackedTangentX.W;

				RawMesh.WedgeTangentX.Add(TangentX);
				RawMesh.WedgeTangentY.Add(TangentY);
				RawMesh.WedgeTangentZ.Add(TangentZ);
				for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
				{
					if (TexCoordIndex >= NumTexCoords)
					{
						RawMesh.WedgeTexCoords[TexCoordIndex].AddDefaulted();
					}
					else
					{
						RawMesh.WedgeTexCoords[TexCoordIndex].Add(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetVertexUV(VertexIndexForWedge, TexCoordIndex));
						MeshTracker.bValidTexCoords[TexCoordIndex] = true;
					}
				}

				if (LODData.StaticVertexBuffers.ColorVertexBuffer.IsInitialized())
				{
					RawMesh.WedgeColors.Add(LODData.StaticVertexBuffers.ColorVertexBuffer.VertexColor(VertexIndexForWedge));
					MeshTracker.bValidColors = true;
				}
				else
				{
					RawMesh.WedgeColors.Add(FColor::White);
				}
			}

			int32 MaterialIndex = SkelMeshSection.MaterialIndex;
			if (SrcLODInfo.LODMaterialMap.IsValidIndex(SectionIndex) && SrcLODInfo.LODMaterialMap[SectionIndex] != INDEX_NONE)
			{
				MaterialIndex = FMath::Clamp<int32>(SrcLODInfo.LODMaterialMap[SectionIndex], 0, InComponent->SkeletalMesh->Materials.Num());
			}

			for (uint32 TriIndex = 0; TriIndex < SkelMeshSection.NumTriangles; TriIndex++)
			{
				RawMesh.FaceMaterialIndices.Add(MaterialIndex);
				RawMesh.FaceSmoothingMasks.Add(0);
			}
		}
	}
}

bool IsValidSkeletalMeshComponent(USkeletalMeshComponent* InComponent)
{
	return InComponent && InComponent->MeshObject && InComponent->IsVisible();
}

UStaticMesh * MeshUtils::SkeletalMeshComponentToStaticMesh(USkeletalMeshComponent *SkeletalMeshComponent)
{
	UStaticMesh* StaticMesh = nullptr;

	
	FString MeshName = FGuid::NewGuid().ToString();
	StaticMesh = NewObject<UStaticMesh>(nullptr, *MeshName, RF_Transient);
	StaticMesh->InitResources();




	FRawMesh RawMesh;
	FMeshTracker MeshTracker;

	int32 OverallMaxLODs = 0;

	const FTransform& InRootTransform = FTransform::Identity;
	FMatrix WorldToRoot = InRootTransform.ToMatrixWithScale().Inverse();
	FMatrix ComponentToWorld = SkeletalMeshComponent->GetComponentTransform().ToMatrixWithScale() * WorldToRoot;

	if (IsValidSkeletalMeshComponent(SkeletalMeshComponent))
	{
		SkeletalMeshToRawMeshes(SkeletalMeshComponent, OverallMaxLODs, ComponentToWorld, MeshTracker, RawMesh);
	}


	return StaticMesh;
}
