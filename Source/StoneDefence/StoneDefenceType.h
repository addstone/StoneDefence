// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefenceType.generated.h"

UENUM(BlueprintType)
enum class ESubmissionSkillRequestType :uint8
{
	AUTO,			//生成权力交给服务器
	MANUAL,			//生成权力交给客户都
};

UENUM(BlueprintType)
enum class ESkillType :uint8
{
	BURST,		//一次造成的伤害
	SECTION,	//在一定范围内属性提升 时间过来就还原
	ITERATION,	//持续一定时间内进行恢复
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