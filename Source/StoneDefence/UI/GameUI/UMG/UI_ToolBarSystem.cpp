// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_ToolBarSystem.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "../../Core/UI_RuleOfTheWidget.h"

#define LOCTEXT_NAMESPACE "UUI_ToolBarSystem"

void UUI_ToolBarSystem::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_ToolBarSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//����ʱ
	GameCount->SetText(FText::FromString(GetCurrentCount(GetGameState()->GetGameData().GameCount)));
	//��ҽ��
	GameGlob->SetText(FText::Format(LOCTEXT("GameGlob", "Glob: {0}"), GetPlayerState()->GetPlayerData().GameGold));
	//����������
	TowersDeathNumber->SetText(FText::Format(LOCTEXT("TowersDeathNumber", "TowersDeathNumber : {0}"), GetGameState()->GetGameData().TowersDeathNumber));
	//ɱ����������
	KillSoldier->SetText(FText::Format(LOCTEXT("KillSoldier", "KillSoldier : {0}"), GetGameState()->GetGameData().KillMonstersNumber));
	//��ǰ���ж��ٹ���
	GSQProgressBar->SetPercent(GetGameState()->GetGameData().GetPerOfRemMonsters());
	//��ǰ�׶� 04/04
	GameLevelSurplusQuantity->SetText(FText(
		FText::FromString(FString::Printf(TEXT("%2d / %2d"), 
			GetGameState()->GetGameData().MaxStagesAreMonsters, 
			GetGameState()->GetGameData().MaxStagesAreMonsters - GetGameState()->GetGameData().PerNumberOfMonsters.Num()))));
}

FString UUI_ToolBarSystem::GetCurrentCount(float NewTimeCount)
{
	const int32 NewOurTime = FMath::Max(0, FMath::TruncToInt(NewTimeCount));
	const int32 NewMinrutes = NewOurTime / 60;
	const int32 NewSeconds = NewOurTime % 60;
	return FString::Printf(TEXT("%02d:%02d"), NewMinrutes, NewSeconds); //00 : 00
}

#undef LOCTEXT_NAMESPACE
