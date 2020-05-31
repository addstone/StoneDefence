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
#include "Bullet/RuleOfTheBullet.h"


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

	SpawnMainTowersRule();
}


void AStoneDefenceGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		CallUpdateAllClient([&](ATowersDefencePlayerController *MyPlayerController)
		{
			if (ATowersDefencePlayerState *InPlayerState = MyPlayerController->GetPlayerState<ATowersDefencePlayerState>())
			{
				InPlayerState->GetPlayerData().GameGoldTime += DeltaSeconds;

				if (InPlayerState->GetPlayerData().IsAllowIncrease())
				{
					InPlayerState->GetPlayerData().GameGoldTime = 0;
					InPlayerState->GetPlayerData().GameGold++;
				}
			}
		}
		);



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
	//���ɹ���
	SpawnMonstersRule(DeltaSeconds);

	//���¼���
	UpdateSkill(DeltaSeconds);
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
				//�õ��ȼ�
				DifficultyDetermination.Level += (float)Tmp->GetCharacterData().Lv;
				DifficultyDetermination.Attack += Tmp->GetCharacterData().GetAttack();
				DifficultyDetermination.Defense += Tmp->GetCharacterData().GetArmor();
				Index++;
			}
		}

		DifficultyDetermination.Level /= Index; //ƽ��ֵ������ �������ʼ�ȼ�
		DifficultyDetermination.Attack /= Index; //������ƽ��ֵ
		DifficultyDetermination.Defense /= Index; //������ƽ��ֵ

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
	//ReturnLevel += FMath::Abs(2 - FMath::Sqrt(TowersDD.Variance / 10.f));

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
								if (MyMonster->GetTeamType() == TargetPoint->Team)
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

void AStoneDefenceGameMode::SpawnMainTowersRule()
{
	for (ASpawnPoint *TargetPoint : StoneDefenceUtils::GetAllActor<ASpawnPoint>(GetWorld()))
	{
		if (TargetPoint->Team == ETeam::RED)
		{
			SpawnTower(0, 1, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
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
			auto GetCharacterData = [&](int32 ID) ->const FCharacterData*
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

			if (const FCharacterData *CharacterData = GetCharacterData(CharacterID))
			{
				//https://blog.csdn.net/qq_29523119/article/details/84455486
				UClass *NewClass = CharacterData->CharacterBlueprintKey.LoadSynchronous();
				if (GetWorld() && NewClass)
				{
					if (ARuleOfTheCharacter *RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotator))
					{
						//RuleOfTheCharacter->GetUniqueID();
						//RuleOfTheCharacter->GUID = FGuid::NewGuid();
						FCharacterData &CharacterDataInst = InGameState->AddCharacterData(RuleOfTheCharacter->GUID, *CharacterData);
						CharacterDataInst.UpdateHealth();


						if (CharacterLevel > 1)
						{
							for (int32 i = 0; i < CharacterLevel; i++)
							{
								CharacterDataInst.UpdateLevel();
							}
						}

						InGameState->InitSkill(CharacterDataInst);
						RuleOfTheCharacter->RegisterTeam();
						InCharacter = RuleOfTheCharacter;
					}
				}
			}
		}
	}
	return InCharacter;
}

void AStoneDefenceGameMode::UpdateSkill(float DeltaSeconds)
{
	//auto GetTeam = [&](TArray<TPair<FGuid, FCharacterData>*> &TeamArray,TPair<FGuid, FCharacterData> &Onwer,float InRange,bool bReversed = false)
	//{
	//	auto TeamIner = [&](TPair<FGuid, FCharacterData> &Target)
	//	{
	//		if (InRange != 0)
	//		{
	//			float Distance = (Target.Value.Location - Onwer.Value.Location).Size();
	//			if (Distance <= InRange)
	//			{
	//				TeamArray.Add(&Target);
	//			}
	//		}
	//		else
	//		{
	//			TeamArray.Add(&Target);
	//		}
	//	};

	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		auto TeamIner = [](TArray<FCharacterData*> &TeamArray, FCharacterData* CharacterData, const FVector &Loc, float InRange)
		{
			if (InRange != 0)
			{
				float Distance = (CharacterData->Location - Loc).Size();
				if (Distance <= InRange)
				{
					TeamArray.Add(CharacterData);
				}
			}
			else
			{
				TeamArray.Add(CharacterData);
			}
		};

		//��ȡ��Χ ��Ч�Ѿ�
		auto GetTeam = [&](TArray<FCharacterData*> &TeamArray, ETeam Type, const FVector &Loc, float InRange, bool bReversed = false)
		{
			for (auto &Tmp : InGameState->GetSaveData()->CharacterDatas)
			{
				if (bReversed)
				{
					if (Tmp.Value.Team == Type)
					{
						TeamIner(TeamArray, &Tmp.Value, Loc, InRange);
					}
				}
				else
				{
					if (Tmp.Value.Team != Type)
					{
						TeamIner(TeamArray, &Tmp.Value, Loc, InRange);
					}
				}
			}
		};

		auto IsVerificationSkill = [](const FCharacterData &CharacterSkill, int32 SkillID) -> bool
		{
			for (auto &InSkill : CharacterSkill.AdditionalSkillData)
			{
				if (InSkill.Value.ID == SkillID)
				{
					return true;
				}
			}
			return false;
		};

		//��Ӽ���
		auto AddSkill = [&](FCharacterData* &CharacterElement, FSkillData &InSkill)
		{
			if (!IsVerificationSkill(*CharacterElement, InSkill.ID))
			{
				FGuid MySkillID = FGuid::NewGuid();
				CharacterElement->AdditionalSkillData.Add(MySkillID, InSkill);

				//֪ͨ�ͻ��˸�����ӵ�UI
				CallUpdateAllClient([&](ATowersDefencePlayerController *MyPlayerController) {
					MyPlayerController->AddSkillSlot_Client(MySkillID);
				});
			}
		};

		//�����ɫ���ͬ������
		auto AddSkills = [&](TArray<FCharacterData*> &RecentForces, FSkillData &InSkill)
		{
			//for (auto &CharacterElement : RecentForces)
			//{
			//	InGameState->AddSkill(*CharacterElement, InSkill);
			//}
			for (auto &CharacterElement : RecentForces)
			{
				if (!IsVerificationSkill(*CharacterElement, InSkill.ID))
				{

					//����

					FGuid MySkillID = FGuid::NewGuid();
					CharacterElement->AdditionalSkillData.Add(MySkillID, InSkill);
				}
			}
		};

		//Ѱ��������Ǹ�����Ŀ��
		auto FindRangeTargetRecently = [&](const TPair<FGuid, FCharacterData> &InOwner,bool bReversed = false) -> FCharacterData*
		{
			float TargetDistance = 99999999;
			FGuid Index;

			auto InitTargetRecently = [&](TPair<FGuid, FCharacterData> &Pair)
			{
				FVector Location = Pair.Value.Location;
				FVector TmpVector = Location - InOwner.Value.Location;
				float Distance = TmpVector.Size();

				if (Distance < TargetDistance && Pair.Value.Health > 0)
				{
					Index = Pair.Key;
					TargetDistance = Distance;
				}
			};

			for (auto &Tmp : InGameState->GetSaveData()->CharacterDatas)
			{
				if (InOwner.Key != Tmp.Key) //�ų��Լ�
				{
					if (bReversed)
					{
						//Ѱ�ҵ���
						if (InOwner.Value.Team != Tmp.Value.Team)
						{
							InitTargetRecently(Tmp);
						}
					}
					else
					{
						//Ѱ���Ѿ�
						if (InOwner.Value.Team == Tmp.Value.Team)
						{
							InitTargetRecently(Tmp);
						}		
					}	
				}
			}

			if (Index != FGuid())
			{
				return &InGameState->GetSaveData()->CharacterDatas[Index];
			}

			return nullptr;
		};

		//��ȡ��ģ��
		const TArray<FSkillData*> &SkillDataTemplate = InGameState->GetSkillDataFromTable();

		for (auto &Tmp : InGameState->GetSaveData()->CharacterDatas)
		{
			//����͸���
			TArray<FGuid> RemoveSkill;
			for (auto &SkillTmp : Tmp.Value.AdditionalSkillData)
			{


				if (SkillTmp.Value.SkillType.SkillType == ESkillType::BURST)
				{
					RemoveSkill.Add(SkillTmp.Key);
				}

				//ʱ�䵽����Ȼ�Ƴ�
				if (SkillTmp.Value.SkillType.SkillType == ESkillType::SECTION ||
					SkillTmp.Value.SkillType.SkillType == ESkillType::ITERATION)
				{
					SkillTmp.Value.SkillDuration += DeltaSeconds;
					if (SkillTmp.Value.SkillDuration >= SkillTmp.Value.MaxSkillDuration)
					{
						RemoveSkill.Add(SkillTmp.Key);
					}
				}

				//���� ���г������¼���
				if (SkillTmp.Value.SkillType.SkillType == ESkillType::ITERATION)
				{
					SkillTmp.Value.SkillDurationTime += DeltaSeconds;
					if (SkillTmp.Value.SkillDurationTime >= 1.0f)
					{
						SkillTmp.Value.SkillDurationTime = 0.0f;

						if (SkillTmp.Value.SkillType.SkillEffectType == ESkillEffectType::ADD)
						{
							Tmp.Value.Health += SkillTmp.Value.Health;
							Tmp.Value.PhysicalAttack += SkillTmp.Value.PhysicalAttack;
							Tmp.Value.Armor += SkillTmp.Value.Armor;
							Tmp.Value.AttackSpeed += SkillTmp.Value.AttackSpeed;
							Tmp.Value.Glod += SkillTmp.Value.Glod;
						}
						else
						{
							Tmp.Value.Health -= SkillTmp.Value.Health;
							Tmp.Value.PhysicalAttack -= SkillTmp.Value.PhysicalAttack;
							Tmp.Value.Armor -= SkillTmp.Value.Armor;
							Tmp.Value.AttackSpeed -= SkillTmp.Value.AttackSpeed;
							Tmp.Value.Glod -= SkillTmp.Value.Glod;
						}
					}
				}
				//֪ͨ�ͻ��˽�����Ч�ӵ�����
				CallUpdateAllClient([&](ATowersDefencePlayerController *MyPlayerController) {
					MyPlayerController->SpawnBullet_Client(Tmp.Key, SkillTmp.Value.BulletClass);
				});
			}

			//����
			for (FGuid &RemoveID : RemoveSkill)
			{
				Tmp.Value.AdditionalSkillData.Remove(RemoveID);
			}

			//�����ͷ�
			for (auto &InSkill : Tmp.Value.CharacterSkill)
			{
				InSkill.CDTime += DeltaSeconds;

				//����
				if (InSkill.CDTime >= InSkill.CD)
				{
					InSkill.CDTime = 0.f;

					if (InSkill.SkillType.SkillAttackType == ESkillAttackType::MULTIPLE)
					{
						TArray<FCharacterData*> Recent;
						if (InSkill.SkillType.TargetType == ESkillTargetType::FRIENDLY_FORCES)
						{							
							GetTeam(Recent, Tmp.Value.Team, Tmp.Value.Location, InSkill.AttackRange);
						}
						else if (InSkill.SkillType.TargetType == ESkillTargetType::ENEMY)
						{
							GetTeam(Recent, Tmp.Value.Team, Tmp.Value.Location, InSkill.AttackRange, true);
						}
						AddSkills(Recent, InSkill);
					}
					else if (InSkill.SkillType.SkillAttackType == ESkillAttackType::SINGLE)
					{
						FCharacterData* Recent = nullptr;
						if (InSkill.SkillType.TargetType == ESkillTargetType::FRIENDLY_FORCES)
						{
							Recent = FindRangeTargetRecently(Tmp);
						}
						else if (InSkill.SkillType.TargetType == ESkillTargetType::ENEMY)
						{
							Recent = FindRangeTargetRecently(Tmp, true);
						}
						AddSkill(Recent, InSkill);
					}
				}
			}



			
		}
	}
}

void AStoneDefenceGameMode::CallUpdateAllClient(TFunction<void(ATowersDefencePlayerController *MyPlayerController)> InImplement)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		if (ATowersDefencePlayerController *MyPlayerController = Cast<ATowersDefencePlayerController>(It->Get()))
		{
			InImplement(MyPlayerController);
		}
	}
}
