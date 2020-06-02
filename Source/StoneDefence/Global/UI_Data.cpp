#include "UI_Data.h"
#include "../Character/Core/RuleOfTheCharacter.h"


FGuid TowerICOGUID;
AActor *TowerDoll = nullptr;
bool bLockGUID = false;
int32 PlayerSkillNumber = 0;

ARuleOfTheCharacter *ClickedTargetTower = nullptr;
ARuleOfTheCharacter *ClickedTargetMonster = nullptr;