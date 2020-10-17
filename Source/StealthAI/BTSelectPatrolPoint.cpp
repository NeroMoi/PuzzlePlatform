// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectPatrolPoint.h"
#include"StealthAI.h"
#include"AIPatrolController.h"
#include"AIPatrolPoint.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"Engine.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAIPatrolController *AICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		/* get bb component*/

		UBlackboardComponent *BlackboardComp = AICon->GetBlackBoardComp();

	//	AAIPatrolPoint *CurrentPoint = Cast<AAIPatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
		TArray<AActor *> AvailablePatrolPoints = AICon->GetPatrolPoints();

		AAIPatrolPoint * NextPatrolPoint = nullptr;


		if (AICon->CurrentPatrolPoint  != AvailablePatrolPoints.Num() -1)
		{
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("walking"));
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[++(AICon->CurrentPatrolPoint)]);
		}
		else// if there not any more points to go
		{
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}
		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
