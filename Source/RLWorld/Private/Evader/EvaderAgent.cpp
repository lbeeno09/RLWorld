// Fill out your copyright notice in the Description page of Project Settings.

#include "Evader/EvaderAgent.h"
#include "Evader/EvaderAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEvaderAgent::AEvaderAgent()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(34.f, 96.0f);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEvaderAIController::StaticClass();
}

void AEvaderAgent::SetSpawnLocation(FVector Location)
{
	SpawnLocation = Location;
}

void AEvaderAgent::ResetActor()
{
	float RandomYaw = UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f);
	FRotator RandomRotation = FRotator(0.0f, RandomYaw, 0.0f);

	SetActorLocationAndRotation(SpawnLocation, RandomRotation);
}
