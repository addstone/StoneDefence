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
	APlayerSkillSlotActor *SpawnPlayerBullet(UWorld *World, int32 SkillID);
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

	template<class T>
	T* GetSave(UWorld *InWorld, const TCHAR *SaveName, int32 SaveIndex = INDEX_NONE, EGameSaveType InFlag = EGameSaveType::NONE)
	{
		FString SlotString;
		if (SaveIndex != INDEX_NONE)
		{
			SlotString = FString::Printf(SaveName, SaveIndex);
		}
		else
		{
			SlotString = SaveName;
			if (SlotString.Contains("%i"))
			{
				SlotString.RemoveFromEnd("_%i");
				SlotString += TEXT("_0");
			}
		}

		T *InSlot = Cast<T>(UGameplayStatics::LoadGameFromSlot(SlotString, 0));
		if (!InSlot)
		{
			InSlot = Cast<T>(UGameplayStatics::CreateSaveGameObject(T::StaticClass()));
			if (InSlot)
			{
				InSlot->InitSaveGame(InWorld);
			}		
		}


		return InSlot;
	}

	//面板Widget 切换
	template<class T, class UserObject>
	UserObject *CreateAssistWidget(T* ThisClass, UClass *AssistClass, USizeBox *WidgetArray)
	{
		UserObject *UserObjectElement = nullptr;
		//播放动画的判断

		if (0)
		{
			//播放 淡入
		}

		if (WidgetArray->GetChildAt(0))
		{
			if (WidgetArray->GetChildAt(0)->IsA(AssistClass))
			{
				//关闭我们的board 淡出

				return UserObjectElement;
			}
			else
			{
				WidgetArray->ClearChildren();
			}
		}

		UserObjectElement = CreateWidget<UserObject>(ThisClass->GetWorld(), AssistClass);
		if (UserObjectElement)
		{
			if (WidgetArray->AddChild(UserObjectElement))
			{
				//
			}
			else
			{
				UserObjectElement->RemoveFromParent();
			}
		}

		return UserObjectElement;
	}

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