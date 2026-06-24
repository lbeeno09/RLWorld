// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerAgent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

APursuerAgent::APursuerAgent()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(34.f, 96.0f);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APursuerAgent::SetSpawnLocation(FVector Location)
{
	SpawnLocation = Location;
}

void APursuerAgent::ResetActor()
{
	float RandomYaw = UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f);
	FRotator RandomRotation = FRotator(0.0f, RandomYaw, 0.0f);

	SetActorLocationAndRotation(SpawnLocation, RandomRotation);
}
