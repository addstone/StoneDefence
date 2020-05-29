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

	FSkillData();

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
		FSkillType SkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
		TAssetPtr<class UTexture2D> Icon;

	//��ӽ��
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float Glod;

	//�������ֵ
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float Health;

	//��ӹ�����
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float PhysicalAttack;

	//��ӻ���
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float Armor;

	//0 ����ȫ�������е��� 
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float AttackRange;

	//���ܳ���ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Dynamic Skills")
		float MaxSkillDuration;

	//���ܶ� ����Ч��ά��һ���׶�
	UPROPERTY()//"Dynamic Skills"
		float SkillDuration;

	//���ܳ���ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Main Skill")
		float CD;
};
