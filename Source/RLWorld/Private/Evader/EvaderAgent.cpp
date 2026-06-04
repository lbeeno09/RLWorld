// Fill out your copyright notice in the Description page of Project Settings.

#include "Evader/EvaderAgent.h"
#include "Evader/EvaderAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEvaderAgent::AEvaderAgent()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(34.f, 96.0f);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEvaderAIController::StaticClass();
}
