// Fill out your copyright notice in the Description page of Project Settings.

#include "Evader/EvaderAIController.h"

AEvaderAIController::AEvaderAIController()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AEvaderAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Missing Behavior Tree Asset Assignment"), *GetName());
	}
}
