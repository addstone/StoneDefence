#pragma once

#include "CoreMinimal.h"
#include "Core/DataCore.h"
#include "../StoneDefenceType.h"
#include "SkillData.generated.h"


class UTexture2D;

USTRUCT(BlueprintType)
struct FSkillData : public FDataCore
{
	GENERATED_BODY()

	typedef FDataCore Super;

	FSkillData();

	virtual void Init() override;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
		FSkillType SkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
		TAssetPtr<class UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
		TSubclassOf<AActor> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
		FText SkillIntroduce;

	//添加金币
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float Glod;

	//添加生命值
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float Health;

	//添加攻击力
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float PhysicalAttack;

	//添加护甲
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float Armor;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float WalkSpeed;

	//0 代表全场景所有敌人 
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float AttackRange;

	//技能持续时间
	UPROPERTY(EditDefaultsOnly, Category = "Dynamic Skills")
		float MaxSkillDuration;

	//技能段 技能效果维持一定阶段
	UPROPERTY()//"Dynamic Skills"
		float SkillDuration;

	//技能间隔 比如 每隔一秒激活一次 这个是具体数值 为迭代类型的技能做准备
	UPROPERTY()//"Dynamic Skills"
		float SkillDurationTime;

	//技能持续时间
	UPROPERTY(EditDefaultsOnly, Category = "Main Skill")
		float CD;

	UPROPERTY()
		float CDTime;

	//主技能
	float GetCDPercent() const;

	//动态技能
	float GetDurationPercent() const;

	//只服务于动态技能
	void ResetDuration();

	//服务于主技能
	void ResetCD();
};
