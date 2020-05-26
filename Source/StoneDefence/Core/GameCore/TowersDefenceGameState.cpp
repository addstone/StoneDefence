// Fill out your copyright notice in the Description page of Project Settings.


#include "TowersDefenceGameState.h"
#include "../../StoneDefenceMacro.h"
#include "../../Character/Core/RuleOfTheCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "../../Character/CharacterCore/Monsters.h"
#include "../../Character/CharacterCore/Towers.h"
#include "../../Data/Save/GameSaveData.h"
#include "Kismet/GameplayStatics.h"
#include "../../Data/Save/GameSaveSlotList.h"
#include "Engine/StaticMeshActor.h"
#include "../../Data/CharacterData.h"
#include "../../Data/PlayerData.h"
#include "../../Data/GameData.h"
#include "../../Items/SpawnPoint.h"
#include "../../StoneDefenceUtils.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

FCharacterData CharacterDataNULL;
FBuildingTower BuildingTowerNULL;

void ATowersDefenceGameState::BeginPlay()
{
	Super::BeginPlay();

	GetGameData().AssignedMonsterAmount();

	//GetSaveData()->CharacterDatas.Empty();
	//if (1)
	//{
	//	SaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	//}
}

void ATowersDefenceGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetGameData().GameCount <= 0.f)
	{
		GetGameData().bGameOver = true;
	}
	else
	{
		GetGameData().GameCount -= DeltaSeconds;
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
		GetGameData().bGameOver = true;
	}
	//���ɹ���
	SpawnMonstersRule(DeltaSeconds);
}

ATowersDefenceGameState::ATowersDefenceGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Towers(TEXT("/Game/GameData/TowersData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Monsters(TEXT("/Game/GameData/MonstersData"));
	AITowerCharacterData = MyTable_Towers.Object;
	AIMonsterCharacterData = MyTable_Monsters.Object;

	for (int32 i = 0; i < 21; i++)
	{
		GetSaveData()->BuildingTowers.Add(FGuid::NewGuid(), FBuildingTower());
	}
}

AMonsters * ATowersDefenceGameState::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<AMonsters>(CharacterID, CharacterLevel, AIMonsterCharacterData, Location, Rotator);
}

ATowers * ATowersDefenceGameState::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator)
{
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, AITowerCharacterData, Location, Rotator);
}

bool ATowersDefenceGameState::SaveGameData(int32 SaveNumber)
{
	if (SaveData && SlotList)
	{
		SlotList->SlotList.AddGameDataByNumber(SaveNumber);
		return UGameplayStatics::SaveGameToSlot(SlotList, FString::Printf(TEXT("SlotList")), 0)
			&&
			UGameplayStatics::SaveGameToSlot(SaveData, FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0);
	}
	return false;
}

bool ATowersDefenceGameState::ReadGameData(int32 SaveNumber)
{
	SaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0));

	return SaveData != NULL;
}

ARuleOfTheCharacter *ATowersDefenceGameState::SpawnCharacter(
	int32 CharacterID, 
	int32 CharacterLevel,
	UDataTable *InCharacterData, 
	const FVector &Location, 
	const FRotator &Rotator)
{
	ARuleOfTheCharacter * InCharacter = nullptr;

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
					AddCharacterData(RuleOfTheCharacter->GUID, *CharacterData);
					InCharacter = RuleOfTheCharacter;
				}
			}
		}
	}

	return InCharacter;
}

AStaticMeshActor* ATowersDefenceGameState::SpawnTowersDoll(int32 ID)
{
	AStaticMeshActor *OutActor = nullptr;
	TArray<const FCharacterData*> InDatas;
	GetTowerDataFromTable(InDatas);
	for (const auto &Tmp : InDatas)
	{
		if (Tmp->ID == ID)
		{
			UClass *NewClass = Tmp->CharacterBlueprintKey.LoadSynchronous();
			if (NewClass)
			{
				if (ARuleOfTheCharacter *RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, FVector::ZeroVector, FRotator::ZeroRotator))
				{
					//AStaticMeshActor
					if (AStaticMeshActor *MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator))
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

	return OutActor;
}

const FCharacterData & ATowersDefenceGameState::AddCharacterData(const FGuid &ID, const FCharacterData &Data)
{
	return GetSaveData()->CharacterDatas.Add(ID, Data);
}

const FBuildingTower & ATowersDefenceGameState::AddBuildingTower(const FGuid &ID, const FBuildingTower &Data)
{
	return GetSaveData()->BuildingTowers.Add(ID, Data);
}

bool ATowersDefenceGameState::RemoveCharacterData(const FGuid &ID)
{
	return GetSaveData()->CharacterDatas.Remove(ID);
}

FCharacterData & ATowersDefenceGameState::GetCharacterData(const FGuid &ID)
{
	if (GetSaveData()->CharacterDatas.Contains(ID))
	{
		return GetSaveData()->CharacterDatas[ID];
	}
	
	SD_print(Error, "The current [%i] is invalid", *ID.ToString());
	return CharacterDataNULL;
}

const FCharacterData & ATowersDefenceGameState::GetCharacterDataByID(int32 ID, ECharacterType Type /*= ECharacterType::TOWER*/)
{
	TArray<const FCharacterData*> Datas;
	switch (Type)
	{
	case ECharacterType::TOWER:
	{
		GetTowerDataFromTable(Datas);
		break;
	}
		
	case ECharacterType::MONSTER:
	{
		GetMonsterDataFromTable(Datas);
		break;
	}
	}

	for (const auto &Tmp : Datas)
	{
		if (Tmp->ID == ID)
		{
			return *Tmp;
		}
	}
	return CharacterDataNULL;
}

FBuildingTower & ATowersDefenceGameState::GetBuildingTower(const FGuid &ID)
{
	if (GetSaveData()->BuildingTowers.Contains(ID))
	{
		return GetSaveData()->BuildingTowers[ID];
	}

	SD_print(Error, "The current [%i] is invalid", *ID.ToString());
	return BuildingTowerNULL;
}

const TArray<const FGuid*> ATowersDefenceGameState::GetBuildingTowersID()
{
	TArray<const FGuid*> TowersID;
	for (const auto &Tmp: GetSaveData()->BuildingTowers)
	{
		TowersID.Add(&Tmp.Key);
	}
	return TowersID;
}

bool ATowersDefenceGameState::GetTowerDataFromTable(TArray<const FCharacterData*> &Datas)
{
	if (!CacheTowerDatas.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("CharacterData"), CacheTowerDatas);
	}

	for (const auto &Tmp : CacheTowerDatas)
	{
		Datas.Add(Tmp);
	}
	
	return Datas.Num() > 0;
}

bool ATowersDefenceGameState::GetMonsterDataFromTable(TArray<const FCharacterData*> &Datas)
{
	if (!CacheMonsterDatas.Num())
	{
		AIMonsterCharacterData->GetAllRows(TEXT("CharacterData"), CacheMonsterDatas);
	}

	for (const auto &Tmp : CacheMonsterDatas)
	{
		Datas.Add(Tmp);
	}

	return Datas.Num() > 0;
}

void ATowersDefenceGameState::RequestInventorySlotSwap(const FGuid &A, const FGuid &B)
{
	FBuildingTower &ASlot = GetBuildingTower(A);
	FBuildingTower &BSlot = GetBuildingTower(B);

	if (ASlot.IsValid()) //����
	{
		FBuildingTower TmpSlot = ASlot;
		ASlot = BSlot;
		BSlot = TmpSlot;
	}
	else //�ƶ�
	{
		ASlot = BSlot;
		BSlot.Init();
	}
}

FPlayerData & ATowersDefenceGameState::GetPlayerData()
{
	return GetSaveData()->PlayerData;
}

FGameInstanceDatas & ATowersDefenceGameState::GetGameData()
{
	return GetSaveData()->GamerDatas;
}

UGameSaveData * ATowersDefenceGameState::GetSaveData()
{
	if (!SaveData)
	{
		SaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	}
	return SaveData;
}

UGameSaveSlotList * ATowersDefenceGameState::GetGameSaveSlotList()
{
	if (!SlotList)
	{
		SlotList = Cast<UGameSaveSlotList>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot")), 0));
		if (!SlotList)
		{
			SlotList = Cast<UGameSaveSlotList>(UGameplayStatics::CreateSaveGameObject(UGameSaveSlotList::StaticClass()));
		}
	}
	return SlotList;
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
				DifficultyDetermination.Attack += Tmp->GetCharacterData().PhysicalAttack;
				DifficultyDetermination.Defense += Tmp->GetCharacterData().Armor;
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
	ReturnLevel += FMath::Abs(2 - FMath::Sqrt(TowersDD.Variance / 10.f));

	return ReturnLevel;
}

void ATowersDefenceGameState::SpawnMonstersRule(float DeltaSeconds)
{
	if (!GetGameData().bCurrentLevelMissionSuccess)
	{
		if (!GetGameData().bGameOver)
		{
			if (GetGameData().PerNumberOfMonsters.Num())
			{
				GetGameData().CurrentSpawnMosnterTime += DeltaSeconds;
				if (GetGameData().IsAllowSpawnMosnter())
				{
					GetGameData().ResetSpawnMosnterTime();
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
						GetGameData().StageDecision();
					}
				}
			}
		}
	}
	else
	{

	}
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif