#include "CharacterData.h"
#include "../StoneDefenceMacro.h"

FCharacterData::FCharacterData() :Super()
{

}

void FCharacterData::Init()
{
	Super::Init();

	Lv = 0;
	MaxHealth = 100.f;
	Health = MaxHealth;
	PhysicalAttack = 10.f;
	Armor = 10.f;
	MaxEmpircalValue = 100.f;
	EmpircalValue = 0.f;
	CD = 2.f;
	AttackSpeed = 0.66f;
	Glod = 80;

	AddGlod = 30;
	AddHealth = 50.f;
	AddPhysicalAttack = 10.f;
	AddArmor = 8.f;
	AddEmpiricalValue = 100.f;
	AddAttackSpeed = 0.001f;
	RestoreHealth = 0.2f;
	WalkSpeed = 356.f;

	Location = FVector::ZeroVector;
	Rotator = FRotator::ZeroRotator;
	Team = ETeam::RED;
}

float FCharacterData::GetEPPercent() const
{
	if (MaxEmpircalValue != 0.f)
	{
		return EmpircalValue / MaxEmpircalValue;
	}

	return 0.0f;
}

void FCharacterData::UpdateHealth()
{
	Health = GetMaxHealth();
}

bool FCharacterData::UpdateEP(float InExp)
{
	EmpircalValue += InExp;
	if (EmpircalValue >= MaxEmpircalValue)
	{
		EmpircalValue -= MaxEmpircalValue;

		UpdateLevel();

		return true;
	}
	return false;
}

void FCharacterData::UpdateLevel()
{
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


	//AddPassiveSkillHealth += ((Lv - 1)*AddPassiveSkillHealth)* (Coefficient - 0.09f);
	//AddPassiveSkillPhyscialAttack += (Lv - 1)*AddPassiveSkillPhyscialAttack *(Coefficient - 0.09f);
	//AddPassiveSkillAttackSpeed += (Lv - 1)*AddPassiveSkillAttackSpeed *(Coefficient - 0.09f);
	//AddPassiveSkillArmor = +(Lv - 1)*AddPassiveSkillArmor * (Coefficient - 0.09f);

	Health = GetMaxHealth();
}

float FCharacterData::GetMaxHealth() const
{
	SKILL_TABLE_ACQUISITION(MaxHealth, Health);
}

float FCharacterData::GetAttack() const
{
	SKILL_TABLE_ACQUISITION(PhysicalAttack, PhysicalAttack);
}

float FCharacterData::GetArmor() const
{
	SKILL_TABLE_ACQUISITION(Armor, Armor);
}

float FCharacterData::GetCD() const
{
	SKILL_TABLE_ACQUISITION_CD(CD);
}

float FCharacterData::GetAttackSpeed() const
{
	SKILL_TABLE_ACQUISITION(AttackSpeed, AttackSpeed);
}

float FCharacterData::GetWalkSpeed() const
{
	SKILL_TABLE_ACQUISITION(WalkSpeed, WalkSpeed);
}
