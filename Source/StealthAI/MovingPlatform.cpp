// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	//adding mobility
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Runing code on the server
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		Location += FVector(Speed*DeltaTime, 0, 0);
		SetActorLocation(Location);
	}

}
