// Fill out your copyright notice in the Description page of Project Settings.


#include "PursuerInteractor.h"
#include "GameFramework/Pawn.h"

void UPursuerInteractor::SpecifyAgentObservation_Implementation(FLearningAgentsObservationSchemaElement& OutObservationSchemaElement, ULearningAgentsObservationSchema* InObservationSchema)
{
	if(InObservationSchema)
	{
		return;
	}

	LocationElement = ULearningAgentsObservations::SpecifyLocationObservation(InObservationSchema, 1.0f, FName("Location"));
	VelocityElement = ULearningAgentsObservations::SpecifyVelocityObservation(InObservationSchema, 1.0f, FName("Velocity"));

	TMap<FName, FLearningAgentsObservationSchemaElement> CharacterMap;
	CharacterMap.Add(FName("Location"), LocationElement);
	CharacterMap.Add(FName("Velocity"), VelocityElement);

	CharacterStructElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, CharacterMap, FName("CharacterState"));

	OutObservationSchemaElement = CharacterStructElement;
}

void UPursuerInteractor::GatherAgentObservation_Implementation(FLearningAgentsObservationObjectElement& OutObservationObjectElement, ULearningAgentsObservationObject* InObservationObject, const int32 AgentId)
{
	AActor* AgentActor = Cast<AActor>(GetAgent(AgentId));
	if(!AgentActor || !InObservationObject)
	{
		return;
	}
	
	const FVector CurrentLoc = AgentActor->GetActorLocation();
	const FVector CurrentVel = AgentActor->GetVelocity();
	const FTransform AgentTransform = AgentActor->GetActorTransform();

	ULearningAgentsObservations::MakeLocationObservation(
		InObservationObject,
		CurrentLoc,
		AgentTransform,
		FName("LocationObservation")
	);
	ULearningAgentsObservations::MakeVelocityObservation(
		InObservationObject,
		CurrentVel,
		AgentTransform,
		FName("VelocityObservation")
	);

	reinterpret_cast<int32&>(OutObservationObjectElement) = reinterpret_cast<const int32&>(CharacterStructElement);
}

void UPursuerInteractor::SpecifyAgentAction_Implementation(FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema)
{
	if(!InActionSchema)
	{
		return;
	}

	ActionElement = ULearningAgentsActions::SpecifyVelocityAction(InActionSchema, 1.0f, FName("MoveAction"));

	TMap<FName, FLearningAgentsActionSchemaElement> ActionMap;
	ActionMap.Add(FName("Movement"), ActionElement);

	OutActionSchemaElement = ULearningAgentsActions::SpecifyStructAction(InActionSchema, ActionMap, FName("CharacterActions"));
}

void UPursuerInteractor::PerformAgentAction_Implementation(const ULearningAgentsActionObject* InActionObject, const FLearningAgentsActionObjectElement& InActionObjectElement, const int32 AgentId)
{
	APawn* AgentPawn = Cast<APawn>(GetAgent(AgentId));
	if(!AgentPawn || !InActionObject)
	{
		return;
	}

	FVector ActionVel = FVector::ZeroVector;
	const FTransform AgentTransform = AgentPawn->GetActorTransform();
		
	ULearningAgentsActions::MakeVelocityAction(
		const_cast<ULearningAgentsActionObject*>(InActionObject),
		ActionVel,
		AgentTransform,
		FName("MoveAction")
	);

	AgentPawn->AddMovementInput(ActionVel);
}
