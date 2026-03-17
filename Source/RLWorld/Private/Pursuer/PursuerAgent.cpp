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

	// Add self to LA Manager
	//TArray<AActor*> ActorList;
	//UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PursuerManager"), ActorList);
	//bool bFoundManager = false;
	//for(AActor* Actor : ActorList)
	//{
	//	ULearningAgentsManager* ManagerComp = Cast<ULearningAgentsManager>(Actor->GetComponentByClass(ULearningAgentsManager::StaticClass()));
	//	if(IsValid(ManagerComp))
	//	{
	//		ManagerComp->AddAgent(this);
	//		bFoundManager = true;
	//	}
	//}
	//if(!bFoundManager)
	//{
	//	UE_LOG(LogTemp, Error, L"No Learning Agents Manager found.");
	//}
}

void APursuerAgent::ResetAgent(const FVector& NewLocation, const FRotator& NewRotation)
{
	FVector SafeLocation = NewLocation + FVector(0.0f, 0.0f, 95.0f);

	SetActorLocationAndRotation(
		SafeLocation,
		NewRotation,
		false,
		nullptr,
		ETeleportType::TeleportPhysics
	);

	if(UCharacterMovementComponent* MoveComp =  GetCharacterMovement())
	{

		MoveComp->StopMovementImmediately();
		MoveComp->ClearAccumulatedForces();

		MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}