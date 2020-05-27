// Fill out your copyright notice in the Description page of Project Settings.


#include "RuleOfTheAIController.h"
#include "RuleOfTheCharacter.h"

ARuleOfTheCharacter * ARuleOfTheAIController::GetTarget()
{
	return Target.Get();
}
//
//void ARuleOfTheAIController::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	if (Role == ROLE_Authority)
//	{
//		if (ARuleOfTheCharacter *InCharacter = Cast<ARuleOfTheCharacter>(GetPawn()))
//		{
//			if (FCharacterData *Data = InCharacter->GetCharacterData())
//			{
//				if (Data->IsValid())
//				{
//					Data->Location = InCharacter->GetActorLocation();
//					Data->Rotator = InCharacter->GetActorRotation();
//				}
//			}
//		}
//	}
//}