#include "SkillData.h"

FSkillData::FSkillData()
	:Super()
{

}

void FSkillData::Init()
{
	Super::Init();

	Glod = 0.f;
	Health = 0.f;
	PhysicalAttack = 0.f;
	Armor = 0.f;
	AttackRange = 0.f;
	MaxSkillDuration = 5.f;
	SkillDuration = 0.f;
	CD = 60.f;
	SkillDurationTime = 0.f;
	CDTime = 0.0f;
	//WalkSpeed = 0.0f;
	//bBecomeEffective = false;
	//SubmissionSkillRequestType = ESubmissionSkillRequestType::AUTO;
}

float FSkillData::GetCDPercent() const
{
	return CD == 0.f ? 0 : (CDTime / CD);
}

float FSkillData::GetDurationPercent() const
{
	return MaxSkillDuration == 0.f ? 0 : (SkillDuration / MaxSkillDuration);
}
