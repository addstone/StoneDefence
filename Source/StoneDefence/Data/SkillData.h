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

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float WalkSpeed;

	//0 ����ȫ�������е��� 
	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
		float AttackRange;

	//���ܳ���ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Dynamic Skills")
		float MaxSkillDuration;

	//���ܶ� ����Ч��ά��һ���׶�
	UPROPERTY()//"Dynamic Skills"
		float SkillDuration;

	//���ܼ�� ���� ÿ��һ�뼤��һ�� ����Ǿ�����ֵ Ϊ�������͵ļ�����׼��
	UPROPERTY()//"Dynamic Skills"
		float SkillDurationTime;

	//���ܳ���ʱ��
	UPROPERTY(EditDefaultsOnly, Category = "Main Skill")
		float CD;

	UPROPERTY()
		float CDTime;

	//������
	float GetCDPercent() const;

	//��̬����
	float GetDurationPercent() const;

	//ֻ�����ڶ�̬����
	void ResetDuration();

	//������������
	void ResetCD();
};
