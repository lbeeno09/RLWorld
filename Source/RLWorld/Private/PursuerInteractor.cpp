// Fill out your copyright notice in the Description page of Project Settings.


#include "PursuerInteractor.h"
#include "LearningAgentsObservations.h"
#include "LearningAgentsActions.h"
#include "LearningAgentsManager.h"
#include "PursuerAgent.h"

void UPursuerInteractor::SpecifyAgentObservation(FLearningAgentsObservationSchemaElement& OutObservationSchemaElement, ULearningAgentsObservationSchema* InObservationSchema)
{
	// Agent Data
	FLearningAgentsObservationSchemaElement VelocityObs = ULearningAgentsObservations::SpecifyVelocityObservation(InObservationSchema, 600.0f);

	TMap<FName, FLearningAgentsObservationSchemaElement> VelocityMap;
	VelocityMap.Add(FName("Velocity"), VelocityObs);

	FLearningAgentsObservationSchemaElement VelocityStruct = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, VelocityMap);

	// Target Data
	FLearningAgentsObservationSchemaElement LocationObs = ULearningAgentsObservations::SpecifyLocationObservation(InObservationSchema, 1000.0f);

	TMap<FName, FLearningAgentsObservationSchemaElement> LocationMap;
	LocationMap.Add(FName("Location"), LocationObs);

	FLearningAgentsObservationSchemaElement LocationStruct = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, LocationMap);

	// Total Struct
	TMap<FName, FLearningAgentsObservationSchemaElement> ObsMap;
	ObsMap.Add(FName("Agent"), VelocityStruct);
	ObsMap.Add(FName("Target"), LocationStruct);

	FLearningAgentsObservationSchemaElement ObsStruct = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, ObsMap);

	OutObservationSchemaElement = ObsStruct;
}

void UPursuerInteractor::GatherAgentObservation(FLearningAgentsObservationObjectElement& OutObservationObjectElement, ULearningAgentsObservationObject* InObservationObject, const int32 AgentId)
{
	APursuerAgent* ObsActor = Cast<APursuerAgent>(GetAgent(AgentId));

	// Agent Velocity
	FVector AgentVelocity = ObsActor->GetVelocity();
	FTransform AgentTransform = ObsActor->GetActorTransform();
	FLearningAgentsObservationObjectElement VelocityObs = ULearningAgentsObservations::MakeVelocityObservation(InObservationObject, AgentVelocity, AgentTransform);

	TMap<FName, FLearningAgentsObservationObjectElement> VelocityMap;
	VelocityMap.Add(FName("Velocity"), VelocityObs);

	FLearningAgentsObservationObjectElement VelocityStruct = ULearningAgentsObservations::MakeStructObservation(InObservationObject, VelocityMap);

	// Target Location
	FVector TargetLocation = TargetObject->GetActorLocation();
	FTransform TargetTransform = TargetObject->GetActorTransform();

	FLearningAgentsObservationObjectElement LocationObs = ULearningAgentsObservations::MakeLocationObservation(InObservationObject, TargetLocation, TargetTransform);

	TMap<FName, FLearningAgentsObservationObjectElement> LocationMap;
	LocationMap.Add(FName("Location"), LocationObs);

	FLearningAgentsObservationObjectElement LocationStruct = ULearningAgentsObservations::MakeStructObservation(InObservationObject, LocationMap);

	// Total Struct
	TMap<FName, FLearningAgentsObservationObjectElement> ObsMap;
	ObsMap.Add(FName("Agent"), VelocityStruct);
	ObsMap.Add(FName("Target"), LocationStruct);

	FLearningAgentsObservationObjectElement ObsStruct = ULearningAgentsObservations::MakeStructObservation(InObservationObject, ObsMap);

	OutObservationObjectElement = ObsStruct;
}

void UPursuerInteractor::SpecifyAgentAction(FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema)
{
	// Agent Data
	FLearningAgentsActionSchemaElement VelocityAct = ULearningAgentsActions::SpecifyVelocityAction(InActionSchema, 600.0f);

	TMap<FName, FLearningAgentsActionSchemaElement> VelocityMap;
	VelocityMap.Add(FName("Velocity"), VelocityAct);
		
	FLearningAgentsActionSchemaElement ActStruct = ULearningAgentsActions::SpecifyStructAction(InActionSchema, VelocityMap);

	OutActionSchemaElement = ActStruct;
}

void UPursuerInteractor::PerformAgentAction(const ULearningAgentsActionObject* InActionObject, const FLearningAgentsActionObjectElement& InActionObjectElement, const int32 AgentId)
{
	APursuerAgent* ActActor = Cast<APursuerAgent>(GetAgent(AgentId));

	// Get Action Struct
	TMap<FName, FLearningAgentsActionObjectElement> ActionStruct;
	ULearningAgentsActions::GetStructAction(ActionStruct, InActionObject, InActionObjectElement);

	// Get Action Velocity
	FLearningAgentsActionObjectElement VelocityElement = *ActionStruct.Find(FName("Velocity"));
	FVector AgentVelocity;
	ULearningAgentsActions::GetVelocityAction(AgentVelocity, InActionObject, VelocityElement, ActActor->GetActorTransform());

	// Perform Action
	ActActor->AddMovementInput(AgentVelocity);
}

void UPursuerInteractor::SetTargetObject(AEvaderAgent*& Target)
{
	if(Target->IsA<AEvaderAgent>() == TargetObject->IsA<AEvaderAgent>())
	{
		TargetObject = Target;
	}
}
