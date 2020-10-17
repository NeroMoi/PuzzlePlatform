// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIPatrol.generated.h"

UCLASS()
class STEALTHAI_API AAIPatrol : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIPatrol();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree * BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent *PawnSensingComp;
private:

	UFUNCTION()
		void OnPlayerCaught(APawn *Pawn);

};
