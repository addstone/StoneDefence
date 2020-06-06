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
#include "Core/GameCore/TowersDefenceGameState.h"
#include "Engine/StaticMeshActor.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleLODLevel.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Bullet/RuleOfTheBullet.h"
#include "Core/GameCore/TowersDefencePlayerState.h"
#include "Bullet/PlayerSkillSlotActor.h"
#include "Data/PlayerSkillData.h"
#include "Modules/ModuleManager.h"
#include "ImageUtils.h"
#include "IImageWrapper.h"
#include "Landscape.h"
#include "Misc/FileHelper.h"
#include "IImageWrapperModule.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

void StoneDefenceUtils::CallUpdateAllClient(UWorld *World, TFunction<void(ATowersDefencePlayerController *MyPlayerController)> InImplement)
{
	if (World)
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			if (ATowersDefencePlayerController *MyPlayerController = Cast<ATowersDefencePlayerController>(It->Get()))
			{
				InImplement(MyPlayerController);
			}
		}
	}
}

void StoneDefenceUtils::CallUpdateAllBaseClient(UWorld *World, TFunction<void(APlayerController *MyPlayerController)> InImplement)
{
	if (World)
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			InImplement(It->Get());
		}
	}
}

APlayerSkillSlotActor * StoneDefenceUtils::SpawnPlayerBullet(UWorld *World, int32 SkillID)
{
	if (ATowersDefencePlayerState *InPlayerState = World->GetFirstPlayerController()->GetPlayerState<ATowersDefencePlayerState>())
	{
		if (const FPlayerSkillData * SkillDataState = InPlayerState->GetPlayerSkillDataFromTable(SkillID))
		{
			if (APlayerSkillSlotActor *PlayerSKillSlot = World->SpawnActor<APlayerSkillSlotActor>(SkillDataState->BulletClass, FVector::ZeroVector, FRotator::ZeroRotator))
			{
				return PlayerSKillSlot;
			}
		}
	}

	return nullptr;
}

ARuleOfTheBullet * StoneDefenceUtils::SpawnBullet(UWorld *World, FGuid CharacterID, UClass *InClass)
{
	TArray<ARuleOfTheCharacter *> Characters;
	StoneDefenceUtils::GetAllActor(World, Characters);

	for (auto &Tmp : Characters)
	{
		if (Tmp->GUID == CharacterID)
		{
			return SpawnBullet(World, Tmp, InClass, Tmp->GetFirePoint()->GetComponentLocation(), Tmp->GetFirePoint()->GetComponentRotation());
		}
	}

	return nullptr;
}

ARuleOfTheBullet * StoneDefenceUtils::SpawnBullet(UWorld *World, ARuleOfTheCharacter *Onwer, const int32 SkillID, const FVector &Loc, const FRotator &Rot)
{
	ARuleOfTheBullet *NewBullet = nullptr;
	if (World)
	{
		if (ATowersDefenceGameState *InGameState = World->GetGameState<ATowersDefenceGameState>())
		{
			if (const FSkillData *InData = InGameState->GetSkillData(SkillID))
			{
				if (ARuleOfTheBullet *Bullet = StoneDefenceUtils::SpawnBullet(World, Onwer, InData->BulletClass, Loc, Rot))
				{
					NewBullet = Bullet;
				}
			}
		}
	}

	return NewBullet;
}

ARuleOfTheBullet * StoneDefenceUtils::SpawnBullet(UWorld *World, APawn *NewPawn, UClass *InClass, const FVector &Loc, const FRotator &Rot)
{
	if (World && NewPawn && InClass)
	{
		FTransform Transform;
		Transform.SetLocation(Loc);
		Transform.SetRotation(Rot.Quaternion());

		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Instigator = NewPawn;

		if (ARuleOfTheBullet *Bullet = World->SpawnActor<ARuleOfTheBullet>(InClass, Transform, ActorSpawnParameters))
		{
			return Bullet;
		}
	}

	return nullptr;
}

AStaticMeshActor* StoneDefenceUtils::SpawnTowersDoll(UWorld *World, int32 ID)
{
	AStaticMeshActor *OutActor = nullptr;
	if (World)
	{
		if (ATowersDefenceGameState *InGameState = World->GetGameState<ATowersDefenceGameState>())
		{
			const TArray<FCharacterData*> &InDatas = InGameState->GetTowerDataFromTable();			
			for (const auto &Tmp : InDatas)
			{
				if (Tmp->ID == ID)
				{
					UClass *NewClass = Tmp->CharacterBlueprintKey.LoadSynchronous();
					if (NewClass)
					{
						if (ARuleOfTheCharacter *RuleOfTheCharacter = World->SpawnActor<ARuleOfTheCharacter>(NewClass, FVector::ZeroVector, FRotator::ZeroRotator))
						{
							//AStaticMeshActor
							if (AStaticMeshActor *MeshActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator))
							{
								FTransform Transform;
								if (UStaticMesh *InMesh = RuleOfTheCharacter->GetDollMesh(Transform, ID))
								{
									MeshActor->SetMobility(EComponentMobility::Movable);
									MeshActor->GetStaticMeshComponent()->SetRelativeTransform(Transform);
									MeshActor->GetStaticMeshComponent()->SetStaticMesh(InMesh);
									MeshActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
									OutActor = MeshActor;
									RuleOfTheCharacter->Destroy();
								}
								else
								{
									MeshActor->Destroy();
									RuleOfTheCharacter->Destroy();
								}
							}
							else
							{
								RuleOfTheCharacter->Destroy();
							}
						}
					}
					break;
				}
			}
		}
	}
	return OutActor;
}

void StoneDefenceUtils::FindRangeTargetRecently(ARuleOfTheCharacter *InOwner, float Range, TArray<ARuleOfTheCharacter *> &Targets)
{
	if (InOwner && Range > 0.0f)
	{
		TArray<ARuleOfTheCharacter *> NewTargets;
		StoneDefenceUtils::GetAllActor(InOwner->GetWorld(), NewTargets);
		for (ARuleOfTheCharacter * Tmp : NewTargets)
		{
			if (InOwner->GetTeamType() != Tmp->GetTeamType())
			{
				if ((InOwner->GetActorLocation() - Tmp->GetActorLocation()).Size() <= Range)
				{
					Targets.Add(Tmp);
				}
			}
		}
	}
}

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

void StoneDefenceUtils::Execution(UWorld *World, const FGuid &CharacterID, TFunction<void(ARuleOfTheCharacter *InCharacter)> Code)
{
	if (World)
	{
		TArray<ARuleOfTheCharacter *> Characters;
		StoneDefenceUtils::GetAllActor(World, Characters);
		for (ARuleOfTheCharacter *Tmp : Characters)
		{
			if (Tmp->GUID == CharacterID)
			{
				Code(Tmp);
				break;
			}
		}
	}
}

float Expression::GetDamage(IRuleCharacter *Enemy, IRuleCharacter *Owner)
{
	if (Enemy && Owner)
	{
		//if (FCharacterData *CharacterData = Owner->GetCharacterData())
		//{
		//	if (FCharacterData *EnemyCharacterData = Enemy->GetCharacterData())
		//	{
				return Enemy->GetCharacterData().GetAttack() / ((Owner->GetCharacterData().GetArmor() / 100.f) + 1.f);
			}
	//	}
	//}

	return 0.0f;
}

UStaticMesh * MeshUtils::ParticleSystemCompnentToStaticMesh(UParticleSystemComponent *NewParticleSystemComponent)
{
	UStaticMesh *NewStaticMesh = nullptr;
	if (NewParticleSystemComponent->Template && NewParticleSystemComponent->Template->Emitters.Num() > 0)
	{
		for (const UParticleEmitter *Tmp : NewParticleSystemComponent->Template->Emitters)
		{
			if (Tmp->LODLevels[0]->bEnabled)
			{
				if (UParticleModuleTypeDataMesh* MyParticleDataMesh = Cast<UParticleModuleTypeDataMesh>(Tmp->LODLevels[0]->TypeDataModule))
				{
					if (MyParticleDataMesh->Mesh)
					{
						NewStaticMesh = MyParticleDataMesh->Mesh;
						break;
					}
				}
			}
		}
	}

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

	if (UWorld *World = SkeletalMeshComponent->GetWorld())
	{
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

		uint32 MaxInUseTextureCoordinate = 0;

		if (!MeshTracker.bValidColors)
		{
			RawMesh.WedgeColors.Empty();
		}

		for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
		{
			if (!MeshTracker.bValidTexCoords[TexCoordIndex])
			{
				RawMesh.WedgeTexCoords[TexCoordIndex].Empty();
			}
			else
			{
				MaxInUseTextureCoordinate = FMath::Max(MaxInUseTextureCoordinate, TexCoordIndex);
			}
		}

		if (RawMesh.IsValidOrFixable())
		{
			FString MeshName = FGuid::NewGuid().ToString();
			StaticMesh = NewObject<UStaticMesh>(World, *MeshName, RF_Transient | RF_Standalone);
			StaticMesh->InitResources();

			StaticMesh->LightingGuid = FGuid::NewGuid();

			const uint32 LightMapIndex = FMath::Min(MaxInUseTextureCoordinate + 1, (uint32)8 - 1);

			FStaticMeshSourceModel& SrcModel = StaticMesh->AddSourceModel();
			SrcModel.BuildSettings.bRecomputeNormals = false;
			SrcModel.BuildSettings.bRecomputeTangents = false;
			SrcModel.BuildSettings.bRemoveDegenerates = true;
			SrcModel.BuildSettings.bUseHighPrecisionTangentBasis = false;
			SrcModel.BuildSettings.bUseFullPrecisionUVs = false;
			SrcModel.BuildSettings.bGenerateLightmapUVs = true;
			SrcModel.BuildSettings.SrcLightmapIndex = 0;
			SrcModel.BuildSettings.DstLightmapIndex = LightMapIndex;
			SrcModel.SaveRawMesh(RawMesh);

			for (const UMaterialInterface* Material : SkeletalMeshComponent->GetMaterials())
			{
				StaticMesh->StaticMaterials.Add(FStaticMaterial(const_cast<UMaterialInterface*>(Material)));
			}

			StaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
			StaticMesh->LightMapCoordinateIndex = LightMapIndex;

			TArray<int32> UniqueMaterialIndices;
			for (int32 MaterialIndex : RawMesh.FaceMaterialIndices)
			{
				UniqueMaterialIndices.AddUnique(MaterialIndex);
			}

			for (int32 i = 0; i < UniqueMaterialIndices.Num(); i++)
			{
				StaticMesh->GetSectionInfoMap().Set(0, i, FMeshSectionInfo(UniqueMaterialIndices[i]));
			}
			StaticMesh->GetOriginalSectionInfoMap().CopyFrom(StaticMesh->GetSectionInfoMap());

			StaticMesh->Build(false);
		}
	}

	return StaticMesh;
}

RenderingUtils::FScreenShot::FScreenShot(
	int32 InWidth,
	int32 InHeight,
	UTexture2D *&InTexture,
	UObject *InOuter,
	int32 InImageQuality /*= 80*/,
	bool bInShowUI /*= false*/,
	bool bAddFilenameSuffix /*= true*/)
	:Texture(InTexture)
	, ScaledWidth(InWidth)
	, ScaledHeight(InHeight)
	, ImageQuality(InImageQuality)
	, Outer(InOuter)
{
	if (!UGameViewportClient::OnScreenshotCaptured().IsBound())
	{
		Filename = FPaths::ProjectSavedDir() / TEXT("SaveGames") / FGuid::NewGuid().ToString();
		ScreenShotDelegateHandle = UGameViewportClient::OnScreenshotCaptured().AddRaw(
			this,
			&RenderingUtils::FScreenShot::OnScreenshotCapturedInternal);

		FScreenshotRequest::RequestScreenshot(Filename, bInShowUI, bAddFilenameSuffix);
		Filename += TEXT(".jpg");
	}
}

void RenderingUtils::FScreenShot::OnScreenshotCapturedInternal(
	int32 SrcWidth,
	int32 SrcHeight,
	const TArray<FColor>& OrigBitmap)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	check(OrigBitmap.Num() == SrcWidth * SrcHeight);

	// 调整图像大小以强制最大大小。 
	TArray<FColor> ScaledBitmap;
	FImageUtils::ImageResize(SrcWidth, SrcHeight, OrigBitmap, ScaledWidth, ScaledHeight, ScaledBitmap, true);

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
	ImageWrapper->SetRaw(ScaledBitmap.GetData(), ScaledBitmap.GetAllocatedSize(), ScaledWidth, ScaledHeight, ERGBFormat::BGRA, 8);

	//jpg资源包头
	const TArray<uint8>& JPEGData = ImageWrapper->GetCompressed(ImageQuality);
	FFileHelper::SaveArrayToFile(JPEGData, *Filename);

	//压缩
	FCreateTexture2DParameters Params;
	Params.bDeferCompression = true;
	Texture = FImageUtils::CreateTexture2D(ScaledWidth, ScaledHeight, ScaledBitmap, Outer, FGuid::NewGuid().ToString(), RF_NoFlags, Params);

	UGameViewportClient::OnScreenshotCaptured().Remove(ScreenShotDelegateHandle);
	ImageWrapper.Reset();

	//结束自己
	delete this;
}

//ASceneCapture2D * RenderingUtils::SpawnSceneCapture2D(UWorld *World, UClass *SceneCaptureClass, FMapSize &MapSize, float Life)
//{
//	if (SceneCaptureClass)
//	{
//		for (TActorIterator<ALandscape> It(World, ALandscape::StaticClass()); It; ++It)
//		{
//			if (ALandscape* BigMap = *It)
//			{
//				//都是正方形
//				FVector BigMapSize = BigMap->GetActorScale3D();
//				MapSize.BigMapRealSize = FVector2D(BigMapSize.X * 7, BigMapSize.Y * 7);
//
//				FVector CenterPoint = FVector(MapSize.BigMapRealSize.X / 2);
//
//				if (ASceneCapture2D *NewCarma = World->SpawnActor<ASceneCapture2D>(SceneCaptureClass, CenterPoint, FRotator(-90.f, 0.f, 0.f)))
//				{
//					if (Life != 0.f)
//					{
//						NewCarma->SetLifeSpan(Life);
//					}
//
//					return NewCarma;
//				}
//
//				break;
//			}
//		}
//	}
//
//	return nullptr;
//}
#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif