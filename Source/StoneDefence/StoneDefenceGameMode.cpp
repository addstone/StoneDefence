// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "StoneDefenceGameMode.h"
#include "Core/GameCore/TowersDefenceGameState.h"
#include "Core/GameCore/TowersDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"
#include "Core/GameCore/TowersDefencePlayerState.h"
#include "UI/GameUI/Core/RuleofTheHUD.h"
#include "StoneDefenceUtils.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Character/CharacterCore/Towers.h"
#include "Items/SpawnPoint.h"
#include "Character/CharacterCore/Monsters.h"
#include "Engine/DataTable.h"

AStoneDefenceGameMode::AStoneDefenceGameMode()
{
	GameStateClass = ATowersDefenceGameState::StaticClass();
	PlayerControllerClass = ATowersDefencePlayerController::StaticClass();
	DefaultPawnClass = ATowerDefenceGameCamera::StaticClass();
	PlayerStateClass = ATowersDefencePlayerState::StaticClass();
	HUDClass = ARuleofTheHUD::StaticClass();
}

void AStoneDefenceGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		InGameState->GetGameData().AssignedMonsterAmount();
	}
}


void AStoneDefenceGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			if (ATowersDefencePlayerState *InPlayerState = It->Get()->GetPlayerState<ATowersDefencePlayerState>())
			{
				InPlayerState->GetPlayerData().GameGoldTime += DeltaSeconds;

				if (InPlayerState->GetPlayerData().IsAllowIncrease())
				{
					InPlayerState->GetPlayerData().GameGoldTime = 0;
					InPlayerState->GetPlayerData().GameGold++;
				}
			}
		}



		if (InGameState->GetGameData().GameCount <= 0.f)
		{
			InGameState->GetGameData().bGameOver = true;
		}
		else
		{
			InGameState->GetGameData().GameCount -= DeltaSeconds;
		}
		int32 TowersNum = 0;
		TArray<ARuleOfTheCharacter*> InTowers;
		StoneDefenceUtils::GetAllActor<ATowers>(GetWorld(), InTowers);
		for (ARuleOfTheCharacter* Tower : InTowers)
		{
			if (Tower->IsActive())
			{
				TowersNum++;
			}
		}
		if (TowersNum == 0)
		{
			InGameState->GetGameData().bGameOver = true;
		}

	}
	//生成怪物
	SpawnMonstersRule(DeltaSeconds);
}

AMonsters * AStoneDefenceGameMode::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<AMonsters>(CharacterID, CharacterLevel, GetGameState<ATowersDefenceGameState>()->AIMonsterCharacterData, Location, Rotator);
}

ATowers * AStoneDefenceGameMode::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, GetGameState<ATowersDefenceGameState>()->AITowerCharacterData, Location, Rotator);
}

int32 GetMonsterLevel(UWorld *InWorld)
{
	struct FDifficultyDetermination
	{
		FDifficultyDetermination()
			:Level(0)
			, Combination(0.f)
			, Attack(0.f)
			, Defense(0.f)
			, Variance(0.f)
		{

		}
		float Level;
		float Combination;
		float Attack;
		float Defense;
		float Variance;
	};

	auto GetDifficultyDetermination = [](TArray<ARuleOfTheCharacter*> &RuleOfTheCharacter)->FDifficultyDetermination
	{
		int32 Index = 0;
		FDifficultyDetermination DifficultyDetermination;
		for (ARuleOfTheCharacter *Tmp : RuleOfTheCharacter)
		{
			if (Tmp->IsActive())
			{
				//拿到等级
				DifficultyDetermination.Level += (float)Tmp->GetCharacterData().Lv;
				DifficultyDetermination.Attack += Tmp->GetCharacterData().PhysicalAttack;
				DifficultyDetermination.Defense += Tmp->GetCharacterData().Armor;
				Index++;
			}
		}

		DifficultyDetermination.Level /= Index; //平均值代表着 怪物的起始等级
		DifficultyDetermination.Attack /= Index; //攻击力平均值
		DifficultyDetermination.Defense /= Index; //防御力平均值

		for (ARuleOfTheCharacter *Tmp : RuleOfTheCharacter)
		{
			if (Tmp->IsActive())
			{
				float InValue = (float)Tmp->GetCharacterData().Lv - DifficultyDetermination.Level;
				DifficultyDetermination.Variance += InValue * InValue;
			}
		}

		DifficultyDetermination.Variance /= Index;

		return DifficultyDetermination;
	};

	TArray<ARuleOfTheCharacter*> Towers;
	TArray<ARuleOfTheCharacter*> Monsters;
	StoneDefenceUtils::GetAllActor<ATowers>(InWorld, Towers);
	StoneDefenceUtils::GetAllActor<AMonsters>(InWorld, Monsters);

	FDifficultyDetermination TowersDD = GetDifficultyDetermination(Towers);
	FDifficultyDetermination MonsterDD = GetDifficultyDetermination(Monsters);

	int32 ReturnLevel = TowersDD.Level;
	if (TowersDD.Attack > MonsterDD.Attack)
	{
		ReturnLevel++;
	}
	if (TowersDD.Defense > MonsterDD.Defense)
	{
		ReturnLevel++;
	}
	ReturnLevel += FMath::Abs(2 - FMath::Sqrt(TowersDD.Variance / 10.f));

	return ReturnLevel;
}

void AStoneDefenceGameMode::SpawnMonstersRule(float DeltaSeconds)
{
	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		if (!InGameState->GetGameData().bCurrentLevelMissionSuccess)
		{
			if (!InGameState->GetGameData().bGameOver)
			{
				if (InGameState->GetGameData().PerNumberOfMonsters.Num())
				{
					InGameState->GetGameData().CurrentSpawnMosnterTime += DeltaSeconds;
					if (InGameState->GetGameData().IsAllowSpawnMosnter())
					{
						InGameState->GetGameData().ResetSpawnMosnterTime();
						int32 MonsterLevel = GetMonsterLevel(GetWorld());

						if (ARuleOfTheCharacter* MyMonster = SpawnMonster(0, MonsterLevel, FVector::ZeroVector, FRotator::ZeroRotator))
						{
							TArray<ASpawnPoint *> MosnterSpawnPoints;
							for (ASpawnPoint* TargetPoint : StoneDefenceUtils::GetAllActor<ASpawnPoint>(GetWorld()))
							{
								if (MyMonster->IsTeam() == TargetPoint->bTeam)
								{
									MosnterSpawnPoints.Add(TargetPoint);
								}
							}
							ASpawnPoint *TargetPoint = MosnterSpawnPoints[FMath::RandRange(0, MosnterSpawnPoints.Num() - 1)];
							MyMonster->SetActorLocationAndRotation(TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
							InGameState->GetGameData().StageDecision();
						}
					}
				}
			}
		}
		else
		{

		}
	}
}

ARuleOfTheCharacter *AStoneDefenceGameMode::SpawnCharacter(
	int32 CharacterID,
	int32 CharacterLevel,
	UDataTable *InCharacterData,
	const FVector &Location,
	const FRotator &Rotator)
{
	ARuleOfTheCharacter * InCharacter = nullptr;

	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		if (InCharacterData)
		{
			TArray<FCharacterData*> Datas;
			InCharacterData->GetAllRows(TEXT("CharacterData"), Datas);
			auto GetCharacterData = [&](int32 ID) ->FCharacterData*
			{
				for (auto &Tmp : Datas)
				{
					if (Tmp->ID == ID)
					{
						return Tmp;
					}
				}
				return nullptr;
			};

			//auto GetCharacterData = [&](int32 ID) ->const FCharacterData*
			//{
			//	for (auto &Tmp : Datas)
			//	{
			//		if (Tmp->ID == ID)
			//		{
			//			return Tmp;
			//		}
			//	}

			//	return nullptr;
			//};

			if (FCharacterData *CharacterData = GetCharacterData(CharacterID))
			{
				//https://blog.csdn.net/qq_29523119/article/details/84455486
				UClass *NewClass = CharacterData->CharacterBlueprintKey.LoadSynchronous();
				if (GetWorld() && NewClass)
				{
					if (ARuleOfTheCharacter *RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotator))
					{
						//RuleOfTheCharacter->GetUniqueID();
						//RuleOfTheCharacter->GUID = FGuid::NewGuid();
						CharacterData->UpdateHealth();


						if (CharacterLevel > 1)
						{
							for (int32 i = 0; i < CharacterLevel; i++)
							{
								CharacterData->UpdateLevel();
							}
						}

						InGameState->AddCharacterData(RuleOfTheCharacter->GUID, *CharacterData);
						InCharacter = RuleOfTheCharacter;
					}
				}
			}
		}
	}
	return InCharacter;
}