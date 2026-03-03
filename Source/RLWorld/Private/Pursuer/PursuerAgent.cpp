// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerAgent.h"
#include "LearningAgentsManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void APursuerAgent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the walk speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	// Store Spawn point
	SpawnLocation = this->GetActorLocation();
	SpawnRotation = this->GetActorRotation();

	// Add self to LA Manager
	TArray<AActor*> ActorList;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PursuerManager"), ActorList);
	bool bFoundManager = false;
	for(AActor* Actor : ActorList)
	{
		ULearningAgentsManager* ManagerComp = Cast<ULearningAgentsManager>(Actor->GetComponentByClass(ULearningAgentsManager::StaticClass()));
		if(IsValid(ManagerComp))
		{
			ManagerComp->AddAgent(this);
			bFoundManager = true;
		}
	}
	if(!bFoundManager)
	{
		UE_LOG(LogTemp, Error, L"No Learning Agents Manager found.");
	}
}

void APursuerAgent::ResetToSpawn()
{
	SetActorLocationAndRotation(
		SpawnLocation,
		SpawnRotation,
		false,
		nullptr,
		ETeleportType::TeleportPhysics
	);
}