// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "StoneDefenceType.h"
#include "EngineUtils.h"


class USizeBox;
class ARuleOfTheCharacter;
class IRuleCharacter;
class UStaticMesh;
class AStaticMeshActor;
class USkeletalMeshComponent;
class UWorld;
class ARuleOfTheBullet;
class APlayerSkillSlotActor;
class ATowersDefencePlayerController;
class ASceneCapture2D;

namespace StoneDefenceUtils
{

	ARuleOfTheCharacter *FindTargetRecently(const TArray<ARuleOfTheCharacter*> &InCharacters,const FVector &Loc);
	
	template<class A, class B>
	void GetAllActor(UWorld *World, TArray<B*> &Array)
	{
		for (TActorIterator<A>It(World, A::StaticClass()); It; ++It)
		{
			if (B* Tmp = Cast<A>(*It))
			{
				Array.Add(Tmp);
			}
		}
	}

	template<class Type>
	void GetAllActor(UWorld *World, TArray<Type*> &Array)
	{
		for (TActorIterator<Type>It(World, Type::StaticClass()); It; ++It)
		{
			Array.Add(*It);
		}
	}

	//获取比较少的数组
	template<class Type>
	TArray<Type*> GetAllActor(UWorld *World)
	{
		TArray<Type*> Array;
		for (TActorIterator<Type>It(World, Type::StaticClass()); It; ++It)
		{
			if (Type* A = Cast<Type>(*It))
			{
				Array.Add(A);
			}
		}

		return Array;
	}
}

namespace Expression
{
	float GetDamage(IRuleCharacter *Enemy, IRuleCharacter *Owner);
}

namespace MeshUtils
{
	UStaticMesh *ParticleSystemCompnentToStaticMesh(UParticleSystemComponent *NewParticleSystemComponent);
	UStaticMesh *SkeletalMeshComponentToStaticMesh(USkeletalMeshComponent *SkeletalMeshComponent);
}