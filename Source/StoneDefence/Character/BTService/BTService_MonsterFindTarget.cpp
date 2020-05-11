// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_MonsterFindTarget.h"
#include "../AIController/MonsterAIController.h"
#include "../Core/RuleOfTheCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBTService_MonsterFindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AMonsterAIController* MonsterAIController = Cast<AMonsterAIController>(OwnerComp.GetOwner()))
	{
		if (UBlackboardComponent* MyBlackBoard = OwnerComp.GetBlackboardComponent())
		{
			if (ARuleOfTheCharacter* NewTarget = Cast<ARuleOfTheCharacter>(MonsterAIController->FindTarget()))
			{
				if (Target != NewTarget) 
				{
					if (ARuleOfTheCharacter* MonsterSelf = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						MonsterSelf->GetCharacterMovement()->StopMovementImmediately();
					}
					Target = NewTarget;
				}

				if (Target.IsValid())
				{
					if (Target->IsActive())
					{
						MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, Target.Get());
					}
					else
					{
						MyBlackBoard->SetValueAsObject(BlackBoardKey_TargetLocation.SelectedKeyName, nullptr);
					}
				}
				else
				{
					MyBlackBoard->SetValueAsObject(BlackBoardKey_TargetLocation.SelectedKeyName, nullptr);
				}
			}

			if (Target.IsValid())
			{
				FVector Mylocation = MonsterAIController->GetPawn()->GetActorLocation();
				FVector TMDistance = Mylocation - Target->GetActorLocation();
				if (TMDistance.Size() > 2200)
				{
					if (ARuleOfTheCharacter* MonsterAI = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						MonsterAI->bAttack = false;
					}
				}

				MyBlackBoard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, TMDistance.Size());
			}
			else
			{
				MyBlackBoard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, 0.f);
			}
		}
	}
}
