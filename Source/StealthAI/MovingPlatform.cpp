// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	//adding mobility
	SetMobility(EComponentMobility::Movable);
	
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	GlobalStartLocation = GetActorLocation();


	if (HasAuthority())// on the server
	{
		// to the client
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Runing code on the server
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		float journeyLength =(GlobalTargetLocation - GlobalStartLocation).Size();
		float journeyTravelled = (Location - GlobalStartLocation).Size();

		if (journeyTravelled > journeyLength)
		{
			GlobalTargetLocation += GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation - GlobalStartLocation;
			GlobalTargetLocation -= GlobalStartLocation;
		}

		FVector Direction = (GlobalTargetLocation - Location).GetSafeNormal();
		// GetTransform().TransformPosition(TargetLocation);
		// set relative location
		//FVector WorldLocation = GetTransform().TransformPosition(TargetLocation);
		//FVector Direction = (WorldLocation - Location).GetSafeNormal();
		// set absolute position
		//FVector Direction = (TargetLocation - Location).GetSafeNormal();
		Location += Speed*DeltaTime*Direction;
		SetActorLocation(Location);
	}

}
