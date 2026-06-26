// Fill out your copyright notice in the Description page of Project Settings.

#include "Evader/EvaderGoal.h"
#include "NavigationSystem.h"

AEvaderGoal::AEvaderGoal()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEvaderGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEvaderGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEvaderGoal::ResetActor()
{
    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
    if(!NavSys)
    {
        return;
    }

    FVector PreviousLocation = GetActorLocation();
    FNavLocation ResultLocation;
    bool bFoundValidPoint = NavSys->GetRandomPointInNavigableRadius(
        PreviousLocation,
        500.0f,
        ResultLocation
    );

    if(bFoundValidPoint)
    {
        SetSpawnLocation(ResultLocation.Location);
        SetActorLocationAndRotation(ResultLocation.Location, FRotator::ZeroRotator);
    }
}

void AEvaderGoal::SetSpawnLocation(FVector Location)
{
	SpawnLocation = Location;
}
