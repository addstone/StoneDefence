// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskAttackTarget.h"
#include "../AIController/MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Core/RuleOfTheCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type UBTTaskAttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (AMonsterAIController* MyAIConroller = Cast<AMonsterAIController>(OwnerComp.GetOwner()))
	{
		if (UBlackboardComponent* MyBlackBoard = OwnerComp.GetBlackboardComponent())
		{
			if (Blackboard_Actor.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
			{
				if (ARuleOfTheCharacter* MyPawn = Cast<ARuleOfTheCharacter>(MyAIConroller->GetPawn()))
				{
					if (ARuleOfTheCharacter* TargetTower = Cast<ARuleOfTheCharacter>(MyBlackBoard->GetValueAsObject(Blackboard_Actor.SelectedKeyName)))
					{
						MyPawn->AttackBegin();
						MyPawn->bAttack = true;
						MyAIConroller->AttackTarget(TargetTower);
						return EBTNodeResult::Succeeded;
					}
					else
					{
						MyPawn->AttackEnd();
						MyPawn->bAttack = false;
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}

void UBTTaskAttackTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		Blackboard_Actor.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can'Initialize task:%s"), *GetName());
	}
}