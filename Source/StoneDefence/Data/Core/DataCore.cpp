// Fill out your copyright notice in the Description page of Project Settings.


#include "DataCore.h"

FDataCore::FDataCore()
{
	Init();
}

void FDataCore::Init()
{
	Name = NAME_None;
	ID = INDEX_NONE;
	GameGlod = 0;
	Diamonds = 0;
	Copper = 0;
}

bool FDataCore::IsValid() const
{
	return ID != INDEX_NONE;
}
