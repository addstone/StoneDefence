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
	EmpircalValue(MaxEmpircalValue),
	CD(2.f),
	AttackSpeed(0.66),
	Glod(80),

	AddGlod(30),
	AddHealth(0.f),
	AddPhysicalAttack(0.f),
	AddArmor(0.f),
	AddEmpiricalValue(20),
	AddAttackSpeed(0.f),
	RestoreHealth(0.2f),

	AddPassiveSkillHealth(0.f),
	AddContinueHealth(0.f),
	AddPassiveSkillPhyscialAttack(0.f),
	AddPassiveSkillArmor(0),
	ReducePassiveSkillCDTime(0.45f),
	ConstructionTime(5)
{

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
