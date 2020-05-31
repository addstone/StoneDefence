// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tool/ScreenMove.h"
#include "TowersDefencePlayerController.generated.h"

class ATowers;
class AMonsters;

DECLARE_DELEGATE_OneParam(FAddSkillDelegate, FGuid);
DECLARE_DELEGATE_TwoParams(FSpawnBulletDelegate, FGuid, UClass*);
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersDefencePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//�������Ĵ���
	FSimpleDelegate EventMouseMiddlePressed;
	//�ɿ����Ĵ���
	FSimpleDelegate EventFMouseMiddleReleased;
	//��Ӽ��ܵĴ���
	FAddSkillDelegate AddSkillDelegate;
	//�����ӵ��Ĵ���
	FSpawnBulletDelegate SpawnBulletDelegate;

public:
	ATowersDefencePlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetInputModeGameAndUI();

	virtual void SetupInputComponent() override;
	void MouseWheelUP();
	void MouseWheelDown();

	//����м�����
	void MouseMiddleButtonPressed();
	void MouseMiddleButtonReleased();

	const FHitResult &GetHitResult();

	class AStoneDefenceGameMode *GetGameMode();
	class ATowersDefenceGameState *GetGameState();

	UFUNCTION()
		void AddSkillSlot_Client(const FGuid &CharacterID, const FGuid &SlotID);

	UFUNCTION()
		void SpawnBullet_Client(const FGuid &CharacterID,UClass *InClass);

	UFUNCTION()
		AMonsters *SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator);

	UFUNCTION()
		ATowers *SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector &Location, const FRotator &Rotator);


protected:
	FScreenMoveUnits ScreenMoveUnits;

	FHitResult MouseTaceHit;
};
