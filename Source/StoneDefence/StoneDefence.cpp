// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "StoneDefence.h"
#include "Global/RuleOfTheGlobal.h"

void FStoneDefenceModule::StartupModule()
{

}

void FStoneDefenceModule::ShutdownModule()
{
	GManagement.Destory();
	GDollMeshPoolManage.Destory();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FStoneDefenceModule, StoneDefence, "StoneDefence");
DEFINE_LOG_CATEGORY(LogStoneDefence);