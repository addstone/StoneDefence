// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefenceType.generated.h"

UENUM(BlueprintType)
namespace EGameCharacterType
{
	enum Type
	{
		TOWER,
		MAIN_TOWER,
		MONSTER,
		BOSS_MONSTER,
		MAX,
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