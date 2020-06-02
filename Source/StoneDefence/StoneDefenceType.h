// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefenceType.generated.h"

UENUM(BlueprintType)
enum class ESubmissionSkillRequestType :uint8
{
	AUTO,			//����Ȩ������������
	MANUAL,			//����Ȩ�������ͻ���
};

UENUM(BlueprintType)
enum class ESkillType :uint8
{
	BURST,		//һ����ɵ��˺�
	SECTION,	//��һ����Χ���������� ʱ������ͻ�ԭ
	ITERATION,	//����һ��ʱ���ڽ��лָ�
};

UENUM(BlueprintType)
enum class ESkillTargetType :uint8
{
	FRIENDLY_FORCES = 0,
	ENEMY,
};

UENUM(BlueprintType)
enum class ESkillEffectType :uint8
{
	ADD,
	SUBTRACT,
};

USTRUCT(BlueprintType)
struct FSkillType
{
	GENERATED_USTRUCT_BODY()

	FSkillType()
		:SkillType(ESkillType::SECTION)
		, TargetType(ESkillTargetType::FRIENDLY_FORCES)
		, SkillEffectType(ESkillEffectType::ADD)
	{

	}

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		ESkillType SkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		ESkillTargetType TargetType;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		ESkillEffectType SkillEffectType;
};

UENUM()
enum ETeam
{
	RED,
	BLUE,
	MAX,
};

UENUM(BlueprintType)
namespace EGameCharacterType
{
	enum Type
	{
		MINI,
		BOSS,
		MAX
	};
}

UENUM(BlueprintType)
enum class EBulletType :uint8
{
	BULLET_NONE,			//�������κ�Ч��

	BULLET_DIRECT_LINE,		//���ϰ�ֱ�߹���
	BULLET_LINE,			//�Ǹ������ͣ�������ǹ�ӵ���
	BULLET_TRACK_LINE,		//��������
	BULLET_TRACK_LINE_SP,	//��������
	BULLET_RANGE_LINE,		//��Χ�˺��������ף�
	BULLET_RANGE,			//��Χ�˺��������Ա���
	BULLET_CHAIN,			//�������ͣ������˺�����;
};

UENUM(BlueprintType)
enum class ECharacterType :uint8
{
	TOWER,
	MONSTER,
};