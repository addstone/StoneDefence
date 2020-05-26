#include "CharacterData.h"

FCharacterData::FCharacterData()
	:Name(NAME_None),
	ID(INDEX_NONE),
	Lv(1),
	MaxHealth(100),
	Health(MaxHealth),
	PhysicalAttack(10),
	Armor(10),
	MaxEmpircalValue(100),
	EmpircalValue(0.f),
	CD(2.f),
	AttackSpeed(0.66),
	Glod(80),

	AddGlod(30),
	AddHealth(50.f),
	AddPhysicalAttack(10.f),
	AddArmor(8.f),
	AddEmpiricalValue(100),
	AddAttackSpeed(0.001f),
	RestoreHealth(0.2f),

	AddPassiveSkillHealth(0.f),
	AddContinueHealth(0.f),
	AddPassiveSkillPhyscialAttack(0.f),
	AddPassiveSkillArmor(0),
	ReducePassiveSkillCDTime(0.45f),
	ConstructionTime(5)
{

}

float FCharacterData::GetEPPercent() const
{
	if (MaxEmpircalValue != 0.f)
	{
		return EmpircalValue / MaxEmpircalValue;
	}

	return 0.0f;
}

bool FCharacterData::IsValid() const
{
	return ID != INDEX_NONE;
}

void FCharacterData::UpdateHealth()
{
	Health = MaxHealth;
}

bool FCharacterData::UpdateLevel(float InExp)
{
	EmpircalValue += InExp;
	if (EmpircalValue >= MaxEmpircalValue)
	{
		EmpircalValue -= MaxEmpircalValue;

		//被动技能加成
		float Coefficient = .1f;

		Lv += 1;
		Glod += (Lv - 1)*AddGlod * Coefficient;
		MaxHealth += (Lv - 1)*AddHealth * Coefficient;
		PhysicalAttack += (Lv - 1)*AddPhysicalAttack * Coefficient;
		AttackSpeed += (Lv - 1)*AddAttackSpeed * Coefficient;
		Armor += (Lv - 1)*AddArmor * Coefficient;
		MaxEmpircalValue += (Lv - 1)*AddEmpiricalValue * Coefficient;
		RestoreHealth += (RestoreHealth * Lv) / 100;


		AddPassiveSkillHealth += ((Lv - 1)*AddPassiveSkillHealth)* (Coefficient - 0.09f);
		AddPassiveSkillPhyscialAttack += (Lv - 1)*AddPassiveSkillPhyscialAttack *(Coefficient - 0.09f);
		AddPassiveSkillAttackSpeed += (Lv - 1)*AddPassiveSkillAttackSpeed *(Coefficient - 0.09f);
		AddPassiveSkillArmor = +(Lv - 1)*AddPassiveSkillArmor * (Coefficient - 0.09f);

		Health = MaxHealth;

		return true;
	}
	return false;
}
