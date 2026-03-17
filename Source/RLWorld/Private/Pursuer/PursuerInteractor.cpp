// Fill out your copyright notice in the Description page of Project Settings.


#include "Pursuer/PursuerInteractor.h"
#include "Pursuer/PursuerAgent.h"
#include "Evader/EvaderAgent.h"
#include "LearningAgentsObservations.h"
#include "LearningAgentsActions.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPursuerInteractor::SpecifyAgentObservation_Implementation(FLearningAgentsObservationSchemaElement& OutObservationSchemaElement, ULearningAgentsObservationSchema* InObservationSchema)
{
	TMap<FName, FLearningAgentsObservationSchemaElement> ObsMap;

	ObsMap.Add(TEXT("SelfVelocity"), ULearningAgentsObservations::SpecifyVelocityObservation(InObservationSchema, 800.0f));
	ObsMap.Add(TEXT("RelativeTargetLocation"), ULearningAgentsObservations::SpecifyLocationObservation(InObservationSchema, 6000.0f));
	ObsMap.Add(TEXT("TargetVelocity"), ULearningAgentsObservations::SpecifyVelocityObservation(InObservationSchema, 800.0f));

	OutObservationSchemaElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, ObsMap);
}

void UPursuerInteractor::GatherAgentObservation_Implementation(FLearningAgentsObservationObjectElement& OutObservationObjectElement, ULearningAgentsObservationObject* InObservationObject, const int32 AgentId)
{
	APursuerAgent* Pursuer = Cast<APursuerAgent>(GetAgent(AgentId));
	if(!Pursuer || !TargetObject)
	{
		return;
	}

	TMap<FName, FLearningAgentsObservationObjectElement> ObsMap;

	ObsMap.Add(FName("SelfVelocity"), ULearningAgentsObservations::MakeVelocityObservation(InObservationObject, Pursuer->GetVelocity(), Pursuer->GetActorTransform()));
	ObsMap.Add(FName("RelativeTargetLocation"), ULearningAgentsObservations::MakeLocationObservation(InObservationObject, TargetObject->GetActorLocation(), Pursuer->GetActorTransform()));
	ObsMap.Add(FName("TargetVelocity"), ULearningAgentsObservations::MakeVelocityObservation(InObservationObject, TargetObject->GetVelocity(), Pursuer->GetActorTransform()));
	
	OutObservationObjectElement = ULearningAgentsObservations::MakeStructObservation(InObservationObject, ObsMap);
}

void UPursuerInteractor::SpecifyAgentAction_Implementation(FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema)
{
	TMap<FName, FLearningAgentsActionSchemaElement> ActionMap;

	ActionMap.Add(TEXT("MoveAction"), ULearningAgentsActions::SpecifyVelocityAction(InActionSchema, 800.0f));

	OutActionSchemaElement = ULearningAgentsActions::SpecifyStructAction(InActionSchema, ActionMap);
}

void UPursuerInteractor::PerformAgentAction_Implementation(const ULearningAgentsActionObject* InActionObject, const FLearningAgentsActionObjectElement& InActionObjectElement, const int32 AgentId)
{
	APursuerAgent* Pursuer = Cast<APursuerAgent>(GetAgent(AgentId));
	if(!Pursuer)
	{
		return;
	}

	// Get Action Struct
	TMap<FName, FLearningAgentsActionObjectElement> ActionMap;
	ULearningAgentsActions::GetStructAction(ActionMap, InActionObject, InActionObjectElement);

	// Get Action Velocity
	FVector MoveVelocity;
	ULearningAgentsActions::GetVelocityAction(MoveVelocity, InActionObject, ActionMap[TEXT("MoveAction")]);

	// Perform Action
	//Pursuer->AddMovementInput(MoveVelocity.GetSafeNormal(), MoveVelocity.Size() / 800.0f);
	Pursuer->AddMovementInput(Pursuer->GetActorForwardVector(), MoveVelocity.X / 800.0f);
	Pursuer->AddMovementInput(Pursuer->GetActorRightVector(), MoveVelocity.Y / 800.0f);
}
