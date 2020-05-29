// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"
#include "../StoneDefenceType.h"

FPlayerData::FPlayerData()
{
	Init();
}

void FPlayerData::Init()
{
	PlayID = INDEX_NONE;
	Team = ETeam::RED;
	PlayName = NAME_None;
	GameGold = 0;
	Diamonds = 0;
	Copper = 0;
	GameGoldTime = 0.f;
	MaxGameGoldTime = 1.24f;
	SkillIDs.Add(0);
}

bool FPlayerData::IsValid()
{
	return PlayID != INDEX_NONE;
}

bool FPlayerData::IsAllowIncrease()
{
	return GameGoldTime >= MaxGameGoldTime;
}
