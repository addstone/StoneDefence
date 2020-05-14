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

bool FCharacterData::IsValid()
{
	return ID != INDEX_NONE;
}
