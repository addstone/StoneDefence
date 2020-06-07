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
#include "Core/GameCore/TowersDefenceGameInstance.h"



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





	if (UTowersDefenceGameInstance *InGameInstance = GetWorld()->GetGameInstance<UTowersDefenceGameInstance>())
	{
		if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
		{
			if (InGameInstance->GetCurrentSaveSlotNumber() == INDEX_NONE &&
				InGameInstance->GetGameType() == EGameSaveType::NONE)
			{
				InitData();
			}
			else //ͨ���浵��ȡ������
			{
				//�Ӵ浵�ж�ȡ����
				InitDataFormArchives();

				//����浵�ۼ�
				InGameInstance->ClearSaveMark();

				//��ԭ���ǳ����еĽ�ɫ
				for (auto &Tmp : InGameState->GetSaveData()->CharacterDatas)
				{
					if (Tmp.Value.Team == ETeam::RED)
					{
						SpawnTower(Tmp.Value.ID, Tmp.Value.Location, Tmp.Value.Rotator, Tmp.Key);
					}
					else
					{
						SpawnMonster(Tmp.Value.ID, Tmp.Value.Location, Tmp.Value.Rotator, Tmp.Key);
					}
				}
			}
		}
	}
}


void AStoneDefenceGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//������ҵ�����
	UpdatePlayerData(DeltaSeconds);

	//������Ϸ�����Ĺ���
	UpdateGameData(DeltaSeconds);

	//�������ɹ���
	UpdateMonstersRule(DeltaSeconds);

	//���¼���
	UpdateSkill(DeltaSeconds);

	//����װ����
	UpdateInventory(DeltaSeconds);

	//������ҵļ���
	UpdatePlayerSkill(DeltaSeconds);
}

ATowers * AStoneDefenceGameMode::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, GetGameState<ATowersDefenceGameState>()->AITowerCharacterData, Location, Rotator);
}

ATowers * AStoneDefenceGameMode::SpawnTower(int32 CharacterID, const FVector &Location, const FRotator &Rotator, const FGuid &InCharacterGuid /*= FGuid()*/)
{
	return SpawnCharacter<ATowers>(CharacterID, 1, GetGameState<ATowersDefenceGameState>()->AITowerCharacterData, Location, Rotator, InCharacterGuid);
}

AMonsters * AStoneDefenceGameMode::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<AMonsters>(CharacterID, CharacterLevel, GetGameState<ATowersDefenceGameState>()->AIMonsterCharacterData, Location, Rotator);
}

AMonsters * AStoneDefenceGameMode::SpawnMonster(int32 CharacterID, const FVector &Location, const FRotator &Rotator, const FGuid &InCharacterGuid /*= FGuid()*/)
{
	return SpawnCharacter<AMonsters>(CharacterID, 1, GetGameState<ATowersDefenceGameState>()->AIMonsterCharacterData, Location, Rotator, InCharacterGuid);
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
				DifficultyDetermination.Level += (float)Tmp->GetCharacterData()->Lv;
				DifficultyDetermination.Attack += Tmp->GetCharacterData()->GetAttack();
				DifficultyDetermination.Defense += Tmp->GetCharacterData()->GetArmor();
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
				float InValue = (float)Tmp->GetCharacterData()->Lv - DifficultyDetermination.Level;
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

void AStoneDefenceGameMode::UpdateMonstersRule(float DeltaSeconds)
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

void AStoneDefenceGameMode::InitDataFormArchives()
{
	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		//��ʼ����Ϸ����
		InGameState->GetSaveData();

		//��ʼ���洢���б�
		InGameState->GetGameSaveSlotList();

		//��ʼ��������ݱ�
		StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
		{
			if (ATowersDefencePlayerState *InPlayerState = MyPlayerController->GetPlayerState<ATowersDefencePlayerState>())
			{
				InPlayerState->GetSaveData();//��ʼ��������ݱ�
			}
		});
	}
}

void AStoneDefenceGameMode::InitData()
{
	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		InGameState->GetGameData().AssignedMonsterAmount();
		//��������
		SpawnMainTowersRule();
	}
}

ARuleOfTheCharacter *AStoneDefenceGameMode::SpawnCharacter(
	int32 CharacterID,
	int32 CharacterLevel,
	UDataTable *InCharacterData,
	const FVector &Location,
	const FRotator &Rotator,
	const FGuid &InCharacterGuid)
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
						if (InCharacterGuid == FGuid())//�³����Ķ���
						{
							RuleOfTheCharacter->ResetGUID();
							if (FCharacterData *CharacterDataInst = InGameState->AddCharacterData(RuleOfTheCharacter->GUID, *CharacterData))
							{
								CharacterDataInst->UpdateHealth();

								if (CharacterLevel > 1)
								{
									for (int32 i = 0; i < CharacterLevel; i++)
									{
										CharacterDataInst->UpdateLevel();
									}
								}

								//��ʼ����������
								RuleOfTheCharacter->InitSkill();

								//ע����Ӧ�Ķ���
								RuleOfTheCharacter->RegisterTeam();
							}
						}
						else//��ԭ�Ķ���
						{
							RuleOfTheCharacter->GUID = InCharacterGuid;
						}
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


		//��ȡ��Χ ��Ч�Ѿ�
		//auto GetTeam = [&](TArray<TPair<FGuid, FCharacterData>*> &TeamArray, TPair<FGuid, FCharacterData> &InOwner, float InRange, bool bReversed = false)
		//{
		//	auto TeamIner = [&](TPair<FGuid, FCharacterData> &Target)
		//	{
		//		if (InRange != 0)
		//		{
		//			float Distance = (Target.Value.Location - InOwner.Value.Location).Size();
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

		//	for (auto &Tmp : InGameState->GetSaveData()->CharacterDatas)
		//	{
		//		if (bReversed)
		//		{
		//			if (Tmp.Value.Team != InOwner.Value.Team)
		//			{
		//				TeamIner(Tmp);
		//			}
		//		}
		//		else
		//		{
		//			if (Tmp.Value.Team == InOwner.Value.Team)
		//			{
		//				TeamIner(Tmp);
		//			}
		//		}
		//	}
		//};

		////�����ɫ���ͬ������
		//auto AddSkills = [&](TArray<TPair<FGuid, FCharacterData>*> &RecentForces, FSkillData &InSkill)
		//{
		//	//for (auto &CharacterElement : RecentForces)
		//	//{
		//	//	InGameState->AddSkill(*CharacterElement, InSkill);
		//	//}
		//	for (auto &CharacterElement : RecentForces)
		//	{
		//		InGameState->AddSkill(*CharacterElement, InSkill);
		//	}
		//};

		////Ѱ��������Ǹ�����Ŀ��
		//auto FindRangeTargetRecently = [&](const TPair<FGuid, FCharacterData> &InOwner,bool bReversed = false) -> TPair<FGuid, FCharacterData>*
		//{
		//	float TargetDistance = 99999999;
		//	FGuid Index;

		//	auto InitTargetRecently = [&](TPair<FGuid, FCharacterData> &Pair)
		//	{
		//		FVector Location = Pair.Value.Location;
		//		FVector TmpVector = Location - InOwner.Value.Location;
		//		float Distance = TmpVector.Size();

		//		if (Distance < TargetDistance && Pair.Value.Health > 0)
		//		{
		//			Index = Pair.Key;
		//			TargetDistance = Distance;
		//		}
		//	};

		//	for (auto &Tmp : InGameState->GetSaveData()->CharacterDatas)
		//	{
		//		if (InOwner.Key != Tmp.Key) //�ų��Լ�
		//		{
		//			if (bReversed)
		//			{
		//				//Ѱ�ҵ���
		//				if (InOwner.Value.Team != Tmp.Value.Team)
		//				{
		//					InitTargetRecently(Tmp);
		//				}
		//			}
		//			else
		//			{
		//				//Ѱ���Ѿ�
		//				if (InOwner.Value.Team == Tmp.Value.Team)
		//				{
		//					InitTargetRecently(Tmp);
		//				}		
		//			}	
		//		}
		//	}

		//	if (Index != FGuid())
		//	{
		//		for (auto &GameTmp : InGameState->GetSaveData()->CharacterDatas)
		//		{
		//			if (GameTmp.Key == Index)
		//			{
		//				return &GameTmp;
		//			}
		//		}
		//	}

		//	return nullptr;
		//};

		//��ȡ��ģ��
		const TArray<FSkillData*> &SkillDataTemplate = InGameState->GetSkillDataFromTable();

		for (auto &Tmp : InGameState->GetSaveData()->CharacterDatas)
		{
			if (Tmp.Value.Health > 0.f)
			{
				//����͸���
				TArray<FGuid> RemoveSkill;
				for (auto &SkillTmp : Tmp.Value.AdditionalSkillData)
				{
					SkillTmp.Value.SkillDuration -= DeltaSeconds;

					if (SkillTmp.Value.SkillType.SkillType == ESkillType::BURST)
					{
						RemoveSkill.Add(SkillTmp.Key);
					}

					//ʱ�䵽����Ȼ�Ƴ�
					if (SkillTmp.Value.SkillType.SkillType == ESkillType::SECTION ||
						SkillTmp.Value.SkillType.SkillType == ESkillType::ITERATION)
					{

						if (SkillTmp.Value.SkillDuration <= 0)
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


							//֪ͨ�ͻ��˽�����Ч�ӵ�����
							StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController) {
								MyPlayerController->SpawnBullet_Client(Tmp.Key, SkillTmp.Value.ID);
							});
						}
					}
				}

				//����
				for (FGuid &RemoveID : RemoveSkill)
				{
					//֪ͨ�ͻ����Ƴ�����
					StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController) {
						MyPlayerController->RemoveSkillSlot_Server(Tmp.Key, RemoveID);
					});
					Tmp.Value.AdditionalSkillData.Remove(RemoveID);
				}

				TArray<FSkillData> RemoveSkills;
				//�����ͷ�
				for (auto &InSkill : Tmp.Value.CharacterSkill)
				{
					InSkill.CDTime += DeltaSeconds;

					//����
					if (InSkill.CDTime >= InSkill.CD)
					{
						InSkill.CDTime = 0.f;
						if (!InSkill.bBecomeEffective)
						{
// 							if (InSkill.SkillType.SkillAttackType == ESkillAttackType::MULTIPLE)
// 							{
// 								TArray< TPair<FGuid, FCharacterData>*> Recent;
// 								if (InSkill.SkillType.TargetType == ESkillTargetType::FRIENDLY_FORCES)
// 								{
// 									GetTeam(Recent, Tmp, InSkill.AttackRange);
// 								}
// 								else if (InSkill.SkillType.TargetType == ESkillTargetType::ENEMY)
// 								{
// 									GetTeam(Recent, Tmp, InSkill.AttackRange, true);
// 								}
// 								if (Recent.Num())
// 								{
// 									AddSkills(Recent, InSkill);
// 								}
// 							}
// 							else if (InSkill.SkillType.SkillAttackType == ESkillAttackType::SINGLE)
// 							{
// 								TPair<FGuid, FCharacterData>* Recent = nullptr;
// 								if (InSkill.SkillType.TargetType == ESkillTargetType::FRIENDLY_FORCES)
// 								{
// 									Recent = FindRangeTargetRecently(Tmp);
// 								}
// 								else if (InSkill.SkillType.TargetType == ESkillTargetType::ENEMY)
// 								{
// 									Recent = FindRangeTargetRecently(Tmp, true);
// 								}
// 								if (Recent)
// 								{
// 									InGameState->AddSkill(*Recent, InSkill);
// 								}
// 							}
							InSkill.bBecomeEffective = true;
						}
						else
						{
							RemoveSkills.Add(InSkill);
						}
					}
				}
				for (auto &InSkill : RemoveSkills)
				{
					Tmp.Value.CharacterSkill.Remove(InSkill);
					if (InSkill.SubmissionSkillRequestType == ESubmissionSkillRequestType::AUTO)
					{
						//Call�ͻ��� ������Ч�ӵ�����
						StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
						{
							MyPlayerController->SpawnBullet_Client(Tmp.Key, InSkill.ID);
						});
					}
				}				
			}
			
		}
	}
}

void AStoneDefenceGameMode::UpdatePlayerData(float DeltaSeconds)
{
	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
		{
			if (ATowersDefencePlayerState *InPlayerState = MyPlayerController->GetPlayerState<ATowersDefencePlayerState>())
			{
				//��Ϸ��Ҹ���
				InPlayerState->GetPlayerData().GameGoldTime += DeltaSeconds;
				if (InPlayerState->GetPlayerData().IsAllowIncrease())
				{
					InPlayerState->GetPlayerData().GameGoldTime = 0.0f;
					InPlayerState->GetPlayerData().GameGold++;
				}


			}
		}
		);
	}
}

void AStoneDefenceGameMode::UpdateGameData(float DeltaSeconds)
{
	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
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
		for (ARuleOfTheCharacter *Tower : InTowers)
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
}

void AStoneDefenceGameMode::UpdatePlayerSkill(float DeltaSeconds)
{
	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
		{
			if (ATowersDefencePlayerState *InPlayerState = MyPlayerController->GetPlayerState<ATowersDefencePlayerState>())
			{
				for (auto &Tmp : InPlayerState->GetSaveData()->PlayerSkillDatas)
				{
					if (Tmp.Value.IsValid())
					{
						if (Tmp.Value.CDTime > 0.f)
						{
							Tmp.Value.CDTime -= DeltaSeconds;
							Tmp.Value.bBecomeEffective = true;

							//֪ͨ�ͻ��˸������ǵ�װ��CD
							StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
							{
								MyPlayerController->UpdatePlayerSkill_Client(Tmp.Key, true);
							});
						}
						else if (Tmp.Value.bBecomeEffective)
						{
							Tmp.Value.bBecomeEffective = false;

							//֪ͨ�ͻ��˸������ǵ�װ��CD
							StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
							{
								MyPlayerController->UpdatePlayerSkill_Client(Tmp.Key, false);
							});
						}
					}
				}
			}
		}
		);
	}
}

void AStoneDefenceGameMode::UpdateInventory(float DeltaSeconds)
{
	if (ATowersDefenceGameState *InGameState = GetGameState<ATowersDefenceGameState>())
	{
		StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
		{
			if (ATowersDefencePlayerState *InPlayerState = MyPlayerController->GetPlayerState<ATowersDefencePlayerState>())
			{
				for (auto &Tmp : InPlayerState->GetSaveData()->BuildingTowers)
				{
					if (Tmp.Value.IsValid())
					{
						if (!Tmp.Value.bLockCD)
						{
							if (!Tmp.Value.bDragICO)
							{
								if (Tmp.Value.CurrentConstrictionTowersCD > 0)
								{
									Tmp.Value.CurrentConstrictionTowersCD -= DeltaSeconds;
									Tmp.Value.bCallUpdateTowersInfo = true;

									//֪ͨ�ͻ��˸������ǵ�װ��CD
									StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
									{
										MyPlayerController->UpdateInventory_Client(Tmp.Key, true);
									});
								}
								else if (Tmp.Value.bCallUpdateTowersInfo)
								{
									Tmp.Value.bCallUpdateTowersInfo = false;
									//׼����������
									Tmp.Value.TowersPerpareBuildingNumber--;
									Tmp.Value.TowersConstructionNumber++;

									//֪ͨ�ͻ��˸������ǵ�װ��CD
									StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowersDefencePlayerController *MyPlayerController)
									{
										MyPlayerController->UpdateInventory_Client(Tmp.Key, false);
									});

									if (Tmp.Value.TowersPerpareBuildingNumber > 0)
									{
										Tmp.Value.ResetCD();
									}
								}
							}
						}
					}
				}
			}
		}
		);
	}
}
