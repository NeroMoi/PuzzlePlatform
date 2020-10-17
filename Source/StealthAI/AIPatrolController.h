// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()

public:

	AAIPatrolController();

	FORCEINLINE  UBlackboardComponent * GetBlackBoardComp() const { return BlackBoardComp; }
	
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

	// instead to use  a deprecated function Possess()
	virtual void OnPossess(APawn *Pawn) override;

	void SetPlayerCaught(APawn *Pawn);
	void LostPlayerSight();

	int32 CurrentPatrolPoint = 0;

private:

	class UBehaviorTreeComponent * BehaviorComp;
	UBlackboardComponent *BlackBoardComp;

	/*Blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName PlayerKey;

	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName PlayerLocation;

	TArray<AActor*> PatrolPoints;

	
	

};


