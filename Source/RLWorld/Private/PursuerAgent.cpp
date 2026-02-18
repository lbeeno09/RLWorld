// Fill out your copyright notice in the Description page of Project Settings.

#include "PursuerAgent.h"
#include "PursuerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "LearningAgentsManager.h"

void APursuerAgent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the walk speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

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
		}
	}
	if(!bFoundManager)
	{
		UE_LOG(LogTemp, Error, L"No Learning Agents Manager found.");
	}
}
