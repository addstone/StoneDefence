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
	//多播功能
	void CallUpdateAllClient(UWorld *World, TFunction<void(ATowersDefencePlayerController *MyPlayerController)> InImplement);
	void CallUpdateAllBaseClient(UWorld *World, TFunction<void(APlayerController *MyPlayerController)> InImplement);

	ARuleOfTheBullet *SpawnBullet(UWorld *World, FGuid CharacterID, UClass *InClass);
	ARuleOfTheBullet *SpawnBullet(UWorld *World, APawn *NewPawn, UClass *InClass, const FVector &Loc, const FRotator &Rot);
	ARuleOfTheBullet *SpawnBullet(UWorld *World, ARuleOfTheCharacter *Onwer, const int32 SkillID, const FVector &Loc, const FRotator &Rot);


	AStaticMeshActor* SpawnTowersDoll(UWorld *World, int32 ID);

	void FindRangeTargetRecently(ARuleOfTheCharacter *InOwner, float Range, TArray<ARuleOfTheCharacter *> &Targets);

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

	//ARuleOfTheCharacter *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator);

	//template<class T>
	//T *SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable *InCharacterData, const FVector &Location, const FRotator &Rotator)
	//{
	//	return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotator));
	//}
	void Execution(UWorld *World, const FGuid &CharacterID, TFunction<void(ARuleOfTheCharacter *InCharacter)> Code);
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