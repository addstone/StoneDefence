// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "EngineUtils.h"
#include "../../StoneDefenceType.h"
#include "../CharacterCore/Towers.h"
#include "GameFramework/Controller.h"
#include "../Core/RuleOfTheCharacter.h"
#include "../../StoneDefenceUtils.h"

AActor * AMonsterAIController::FindTarget()
{
	//auto GetRecentlyTowers = [&](const TArray<ATowers*> &MyTowers) -> ATowers*
	//{
	//	if (MyTowers.Num())
	//	{
	//		float TowerTagetDistance = 9999999999;
	//		int32 TowersIndex = INDEX_NONE;
	//		const FVector MyLoaction = GetPawn()->GetActorLocation();
	//		for (int32 i = 0; i < MyTowers.Num(); i++)
	//		{
	//			if (ATowers* TowerCharacter = MyTowers[i])
	//			{
	//				FVector Location = TowerCharacter->GetActorLocation();
	//				FVector TmpVector = Location - MyLoaction;
	//				float Distance = TmpVector.Size();

	//				if (Distance < TowerTagetDistance)
	//				{
	//					TowersIndex = i;
	//					TowerTagetDistance = Distance;
	//				}
	//			}
	//		}

	//		if (TowersIndex != INDEX_NONE)
	//		{
	//			return MyTowers[TowersIndex];
	//		}
	//	}
	//	return nullptr;
	//};
	if (!Target.IsValid() || !Target->IsActive())
	{
		TArray<ARuleOfTheCharacter*>TargetMainTowersArray;
		TArray<ARuleOfTheCharacter*>TargetTowersArray;
		for (TActorIterator<ATowers>it(GetWorld(), ATowers::StaticClass()); it; ++it)
		{
			ATowers* TheCharacter = *it;
			if (TheCharacter && TheCharacter->IsActive())
			{
				if (TheCharacter->GetCharacterType() == EGameCharacterType::Type::MINI)
				{
					TargetTowersArray.Add(TheCharacter);
				}
				else if (TheCharacter->GetCharacterType() == EGameCharacterType::Type::BOSS)
				{
					TargetMainTowersArray.Add(TheCharacter);
				}
			}
		}

		//ATowers* MainTowers = GetRecentlyTowers(TargetMainTowersArray);
		//ATowers* NorTowers = GetRecentlyTowers(TargetTowersArray);

		ATowers* MainTowers = Cast<ATowers>(StoneDefenceUtils::FindTargetRecently(TargetMainTowersArray, GetPawn()->GetActorLocation()));
		ATowers* NorTowers = Cast<ATowers>(StoneDefenceUtils::FindTargetRecently(TargetTowersArray, GetPawn()->GetActorLocation()));


		if (MainTowers)
		{
			return MainTowers;
		}
		return NorTowers;
	}
	
	return Target.Get();

}

void AMonsterAIController::AttackTarget(ARuleOfTheCharacter *InTarget)
{

}
