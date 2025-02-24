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

	if (ARuleOfTheAIController* MonsterAIController = Cast<ARuleOfTheAIController>(OwnerComp.GetOwner()))
	{
		if (UBlackboardComponent* MyBlackBoard = OwnerComp.GetBlackboardComponent())
		{
			if (ARuleOfTheCharacter* NewTarget = Cast<ARuleOfTheCharacter>(MonsterAIController->FindTarget()))
			{
				if (MonsterAIController->Target != NewTarget)
				{
					if (ARuleOfTheCharacter* MonsterSelf = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						MonsterSelf->GetCharacterMovement()->StopMovementImmediately();
					}
					MonsterAIController->Target = NewTarget;
				}

				if (MonsterAIController->Target.IsValid())
				{
					if (MonsterAIController->Target->IsActive())
					{
						FVector NewTargetV = MonsterAIController->GetPawn()->GetActorLocation() - MonsterAIController->Target.Get()->GetActorLocation();
						NewTargetV.Normalize();
						FVector CurrentLocation = NewTargetV * 800.f + MonsterAIController->Target.Get()->GetActorLocation();

						MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, MonsterAIController->Target.Get());
						MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, CurrentLocation);

					}
					else
					{
						MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, nullptr);
						MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName,FVector::ZeroVector);

					}
				}
				else
				{
					MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, nullptr);
					MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);

				}
			}
			else
			{
				MyBlackBoard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, nullptr);
				//MyBlackBoard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
			}

			if (MonsterAIController->Target.IsValid())
			{
				FVector Mylocation = MonsterAIController->GetPawn()->GetActorLocation();
				FVector TMDistance = Mylocation - MonsterAIController->Target->GetActorLocation();
				if (TMDistance.Size() > 2200)
				{
					if (ARuleOfTheCharacter* MonsterAI = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						MonsterAI->AttackEnd();
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
