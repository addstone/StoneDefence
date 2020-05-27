// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"

FPlayerSkillData::FPlayerSkillData()
{
	Init();
}

void FPlayerSkillData::Init()
{
	SkillID = INDEX_NONE;
	SkillCD = 0.f;
	MaxSkillCD = 0.f;
	SkillNumber = INDEX_NONE;
}

bool FPlayerSkillData::IsValid()
{
	return SkillID != INDEX_NONE;
}

FPlayerData::FPlayerData()
{
	Init();
}

void FPlayerData::Init()
{
	PlayID = INDEX_NONE;
	bTeam = true;
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
