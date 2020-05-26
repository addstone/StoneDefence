#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SkillData.h"
#include "CharacterData.generated.h"


USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

/*
*!记一次奇怪的编译经历
*由于在Data/Core文件夹下提早创建了CharacterData文件，随后忘记，导致这里莫名其妙的编译不过，排查好久才发现文件重名导致的问题
*/
public:
	FCharacterData();

	//资源
	//////////////////////////////////////////////////////////////////////////
	//角色蓝图实例
	UPROPERTY(EditDefaultsOnly, Category = "Table")
		TAssetSubclassOf<class ARuleOfTheCharacter> CharacterBlueprintKey;
	//属性
	////////////////////////////////////////////////////////
	//角色图片
	UPROPERTY(EditDefaultsOnly, Category = "Table")
		TAssetPtr<class UTexture2D> Icon;

	//角色名字
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		FName Name;

	//ID
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		int32 ID;

	//属性
	////////////////////////////////////////////////////////
	//等级
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Attribute")
		int32 Lv;

	//最大生命值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float MaxHealth;

	//生命值
	UPROPERTY()
		float Health;

	//基础攻击
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float PhysicalAttack;

	//护甲
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float Armor;

	//移动速度
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float WalkSpeed;

	//最大经验值
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float MaxEmpircalValue;

	UPROPERTY()
		float EmpircalValue;

	//CD
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float CD;

	//攻击速度
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float AttackSpeed;

	//如果是塔 则代表花费多少金币可以建造
	//如果是怪物 代表消灭它可以获取多少金币
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		float Glod;

	//角色简介
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
		FText Introduction;

	//增益
	//////////////////////////////////////////////////////////////////////////
	//添加金币
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
		float AddGlod;

	//添加生命值
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
		float AddHealth;

	//添加攻击力
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
		float AddPhysicalAttack;

	//添加护甲
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
		float AddArmor;

	//添加经验值
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
		float AddEmpiricalValue;

	//添加攻击速度
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
		float AddAttackSpeed;

	//自动恢复生命值
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
		float RestoreHealth;

	//塔的技能
	//////////////////////////////////////////////////////////////////////////
	//添加被动生命值
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		float AddPassiveSkillHealth;

	//添加持续恢复生命值
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		float AddContinueHealth;
		
	//添加被动攻击力
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		float AddPassiveSkillPhyscialAttack;

	//添加被动护甲
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		float AddPassiveSkillArmor;

	//添加被动攻击速度
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		float AddPassiveSkillAttackSpeed;

	//减少被动CD
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
		float ReducePassiveSkillCDTime;

	//角色多久建立好
	UPROPERTY(EditDefaultsOnly, Category = "Build")
		float ConstructionTime;

	//技能
	//////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, Category = "Characte Skill")
		TMap<int32, FSkillData> CharacterSkill;


public:
	float GetEPPercent() const;

	bool IsValid() const;

	void UpdateHealth();

	bool UpdateLevel(float InExp);
};