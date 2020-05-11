// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "StoneDefenceType.h"

class USizeBox;
class ARuleOfTheCharacter;
class IRuleCharacter;
class UStaticMesh;
class AStaticMeshActor;
class USkeletalMeshComponent;
class UWorld;
class ARuleOfTheBullet;
class APlayerSkillSlotActor;
class ATowersDefencePlayerController;
class ASceneCapture2D;

namespace StoneDefenceUtils
{

	ARuleOfTheCharacter *FindTargetRecently(const TArray<ARuleOfTheCharacter*> &InCharacters,const FVector &Loc);
	
}
