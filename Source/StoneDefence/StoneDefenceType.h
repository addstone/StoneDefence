// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefenceType.generated.h"

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
	BULLET_NONE,			//不产生任何效果

	BULLET_DIRECT_LINE,		//无障碍直线攻击
	BULLET_LINE,			//非跟踪类型，类似手枪子弹；
	BULLET_TRACK_LINE,		//跟踪类型
	BULLET_TRACK_LINE_SP,	//跟踪类型
	BULLET_RANGE_LINE,		//范围伤害，丢手雷；
	BULLET_RANGE,			//范围伤害，类似自爆；
	BULLET_CHAIN,			//链条类型，持续伤害类型;
};

UENUM(BlueprintType)
enum class ECharacterType :uint8
{
	TOWER,
	MONSTER,
};