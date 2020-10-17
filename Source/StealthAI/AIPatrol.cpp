// Fill out your copyright notice in the Description page of Project Settings.


#include"StealthAI.h"
#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include"StealthAICharacter.h"
// Sets default values
AAIPatrol::AAIPatrol()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//initialize senses'
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSendingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

}

void AAIPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto player = Cast<AStealthAICharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!PawnSensingComp->HasLineOfSightTo(player))
	{
		AAIPatrolController *AIController = Cast<AAIPatrolController>(GetController());
		if (AIController)
		{
			AIController->LostPlayerSight();
		}
	}
}

// Called when the game starts or when spawned
void AAIPatrol::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this,&AAIPatrol::OnPlayerCaught);
		
	}

}



// Called to bind functionality to input
void AAIPatrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIPatrol::OnPlayerCaught(APawn * Pawn)
{
	/*Get a reference to the player controller*/

	AAIPatrolController *AIController = Cast<AAIPatrolController>(GetController());
	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("YOU HAVE BEEN CAUGHT !"));
		AIController->SetPlayerCaught(Pawn);
	}
}

