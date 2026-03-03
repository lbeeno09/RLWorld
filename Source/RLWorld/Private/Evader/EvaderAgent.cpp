// Fill out your copyright notice in the Description page of Project Settings.

#include "Evader/EvaderAgent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEvaderAgent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the walk speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
