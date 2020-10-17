// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthAI.h"
#include "AIPatrol.h"
#include"AIPatrolPoint.h"
#include"BehaviorTree/BehaviorTreeComponent.h"
#include"BehaviorTree/BehaviorTree.h"
#include"AIPatrolController.h"
#include"BehaviorTree/BlackboardComponent.h"
#include "StealthAICharacter.h"

AAIPatrolController::AAIPatrolController()
{
	/*initializer blackboard and behaviorTree*/
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	/*initialize blackboard key*/
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";
	PlayerLocation = "PlayerLocation";

	CurrentPatrolPoint = 0;
}

void AAIPatrolController::OnPossess(APawn * Pawn)
{
	Super::OnPossess(Pawn);
	//get reference to the character
	AAIPatrol*AICharacter = Cast<AAIPatrol>(Pawn);

	if (AICharacter != nullptr)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackBoardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		//populate patrol point array
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIPatrolPoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*(AICharacter->BehaviorTree));
	}

}

void AAIPatrolController::SetPlayerCaught(APawn * Pawn)
{
	if (BlackBoardComp)
	{
		auto player = Cast<AStealthAICharacter>(Pawn);
		if (player)
		{
			BlackBoardComp->SetValueAsObject(PlayerKey, Pawn);
			BlackBoardComp->SetValueAsVector(PlayerLocation, player->GetActorLocation());
		}
	}
}

void AAIPatrolController::LostPlayerSight()
{
	BlackBoardComp->SetValueAsObject(PlayerKey, nullptr);
}
