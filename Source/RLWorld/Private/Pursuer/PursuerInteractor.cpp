// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerInteractor.h"
#include "Pursuer/PursuerAgent.h"
#include "Evader/EvaderAgent.h"
#include "LearningAgentsObservations.h"
#include "LearningAgentsActions.h"
#include "Kismet/GameplayStatics.h"

// --- Observations ---
void UPursuerInteractor::SpecifyAgentObservation_Implementation(FLearningAgentsObservationSchemaElement& OutObservationSchemaElement, ULearningAgentsObservationSchema* InObservationSchema)
{
	TMap<FName, FLearningAgentsObservationSchemaElement> ObservationStruct;

	// Relative Evader Location
	FLearningAgentsObservationSchemaElement RelativeEvader = ULearningAgentsObservations::SpecifyLocationObservation(InObservationSchema, 200.0f);
	ObservationStruct.Add(FName("RelativeEvader"), RelativeEvader);

	// Relative Goal Location
	RelativeEvader = ULearningAgentsObservations::SpecifyLocationObservation(InObservationSchema, 200.0f);
	ObservationStruct.Add(FName("RelativeGoal"), RelativeEvader);

	// Evader Forward
	RelativeEvader = ULearningAgentsObservations::SpecifyDirectionObservation(InObservationSchema);
	ObservationStruct.Add(FName("SelfForward"), RelativeEvader);

	OutObservationSchemaElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, ObservationStruct);
}

void UPursuerInteractor::GatherAgentObservations_Implementation(TArray<FLearningAgentsObservationObjectElement>& OutObservationObjectElements, ULearningAgentsObservationObject* InObservationObject, const TArray<int32>& AgentIds)
{
	TArray<FLearningAgentsObservationObjectElement> ObservationObjectArray;
	for(int32 AgentId : AgentIds)
	{
		APursuerAgent* CurrentAgent = Cast<APursuerAgent>(GetAgent(AgentId));

		TMap<FName, FLearningAgentsObservationObjectElement> ObservationStruct;

		// Relative Evader Location
		FVector RelativeLocation = EvaderActor->GetActorLocation() - CurrentAgent->GetActorLocation();
		FLearningAgentsObservationObjectElement RelativeEvader = ULearningAgentsObservations::MakeLocationObservation(InObservationObject, RelativeLocation, CurrentAgent->GetActorTransform());
		ObservationStruct.Add(FName("RelativeEvader"), RelativeEvader);

		// Relative Goal Location
		RelativeLocation = GoalActor->GetActorLocation() - CurrentAgent->GetActorLocation();
		FLearningAgentsObservationObjectElement RelativeGoal = ULearningAgentsObservations::MakeLocationObservation(InObservationObject, RelativeLocation, CurrentAgent->GetActorTransform());
		ObservationStruct.Add(FName("RelativeGoal"), RelativeGoal);

		// Evader Forward
		FVector PursuerForward = CurrentAgent->GetActorForwardVector();
		FLearningAgentsObservationObjectElement ForwardObservation = ULearningAgentsObservations::MakeDirectionObservation(InObservationObject, PursuerForward, CurrentAgent->GetActorTransform());
		ObservationStruct.Add(FName("SelfForward"), ForwardObservation);

		ObservationObjectArray.Add(ULearningAgentsObservations::MakeStructObservation(InObservationObject, ObservationStruct));
	}
	OutObservationObjectElements = ObservationObjectArray;
}

// --- Actions ---
void UPursuerInteractor::SpecifyAgentAction_Implementation(FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema)
{
	TMap<FName, FLearningAgentsActionSchemaElement> ActionStruct;

	// Move Action
	FLearningAgentsActionSchemaElement MoveAction = ULearningAgentsActions::SpecifyVelocityAction(InActionSchema, 600.0f);
	ActionStruct.Add(FName("RelativeEvader"), MoveAction);

	OutActionSchemaElement = ULearningAgentsActions::SpecifyStructAction(InActionSchema, ActionStruct);
}

void UPursuerInteractor::PerformAgentActions_Implementation(const ULearningAgentsActionObject* InActionObject, const TArray<FLearningAgentsActionObjectElement>& InActionObjectElements, const TArray<int32>& AgentIds)
{
	for(int32 AgentId : AgentIds)
	{
		APursuerAgent* CurrentAgent = Cast<APursuerAgent>(GetAgent(AgentId));
		FLearningAgentsActionObjectElement ActionElement = InActionObjectElements[AgentId];

		TMap<FName, FLearningAgentsActionObjectElement> ActionStruct;
		ULearningAgentsActions::GetStructAction(ActionStruct, InActionObject, ActionElement);

		// Move Action
		FLearningAgentsActionObjectElement MoveAction = *ActionStruct.Find(FName("RelativeEvader"));
		FVector MoveVector;
		ULearningAgentsActions::GetVelocityAction(MoveVector, InActionObject, MoveAction, CurrentAgent->GetActorTransform());

		CurrentAgent->AddMovementInput(MoveVector);
	}
}