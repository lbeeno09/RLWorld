// Fill out your copyright notice in the Description page of Project Settings.

#include "Evader/EvaderAgent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"

void AEvaderAgent::PickNewGoal()
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if(NavSys)
	{
		FNavLocation RandomLocation;
		if(NavSys->GetRandomReachablePointInRadius(FVector::ZeroVector, 5000.0f, RandomLocation))
		{
			CurrentGoalLocation = RandomLocation.Location;
		}
	}
}

void AEvaderAgent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the walk speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	PickNewGoal();
}

void AEvaderAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = (CurrentGoalLocation - GetActorLocation()).GetSafeNormal();
	float DistanceToGoal = FVector::Dist(GetActorLocation(), CurrentGoalLocation);
	if(DistanceToGoal > 150.0f)
	{
		AddMovementInput(Direction, 1.0f);
	}
	else
	{
		PickNewGoal();
	}
}
