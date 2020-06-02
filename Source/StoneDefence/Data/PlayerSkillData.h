#pragma once

#include "CoreMinimal.h"
#include "SkillData.h"
#include "PlayerSkillData.generated.h"



USTRUCT(BlueprintType)
struct FPlayerSkillData : public FSkillData
{
	GENERATED_BODY()

	FPlayerSkillData();

	virtual void Init();

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		int32 SkillNumber;

	//×÷ÎªICOÖ¸Õë
	UPROPERTY(SaveGame)
		class UTexture2D* ICO;
};
