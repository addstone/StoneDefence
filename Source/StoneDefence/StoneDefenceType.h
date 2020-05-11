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