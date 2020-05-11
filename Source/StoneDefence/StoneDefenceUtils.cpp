#include "StoneDefenceUtils.h"
#include "Character/Core/RuleOfTheCharacter.h"

ARuleOfTheCharacter * StoneDefenceUtils::FindTargetRecently(const TArray<ARuleOfTheCharacter*> &InCharacters, const FVector &Loc)
{
	if (InCharacters.Num())
	{
		float TargetDistance = 99999999;
		int32 Index = INDEX_NONE;

		for (int32 i = 0; i < InCharacters.Num(); i++)
		{
			if (ARuleOfTheCharacter* TowerCharacter = InCharacters[i])
			{
				FVector Location = TowerCharacter->GetActorLocation();
				FVector TmpVector = Location - Loc;
				float Distance = TmpVector.Size();

				if (Distance < TargetDistance && TowerCharacter->IsActive())
				{
					Index = i;
					TargetDistance = Distance;
				}
			}
		}

		if (Index != INDEX_NONE)
		{
			return InCharacters[Index];
		}
	}

	return NULL;
}

