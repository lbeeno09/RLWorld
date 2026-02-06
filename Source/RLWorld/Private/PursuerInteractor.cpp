// Fill out your copyright notice in the Description page of Project Settings.


#include "PursuerInteractor.h"
#include "PursuerAgent.h"
#include "GameFramework/Pawn.h"

void UPursuerInteractor::SpecifyAgentObservation_Implementation(FLearningAgentsObservationSchemaElement& OutObservationSchemaElement, ULearningAgentsObservationSchema* InObservationSchema)
{
	FLearningAgentsObservationSchemaElement LocationElement = ULearningAgentsObservations::SpecifyLocationObservation(InObservationSchema, 1.0f);
	FLearningAgentsObservationSchemaElement VelocityElement = ULearningAgentsObservations::SpecifyVelocityObservation(InObservationSchema, 1.0f);

	TMap<FName, FLearningAgentsObservationSchemaElement> CharacterMap;
	CharacterMap.Add(FName("TargetLocation"), LocationElement);
	CharacterMap.Add(FName("SelfVelocity"), VelocityElement);

	CharacterRootElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, CharacterMap);
	OutObservationSchemaElement = CharacterRootElement;
}

void UPursuerInteractor::GatherAgentObservations_Implementation(TArray<FLearningAgentsObservationObjectElement>& OutObservationObjectElement, ULearningAgentsObservationObject* InObservationObject, const TArray<int32>& AgentIds)
{
	for(const int32 AgentId : AgentIds)
	{
		APursuerAgent* Agent = Cast<APursuerAgent>(GetAgent(AgentId));
		if(!Agent || !Agent->TargetObject)
		{
			continue;
		}

		ULearningAgentsObservations::MakeLocationObservation(
			InObservationObject,
			Agent->TargetObject->GetActorLocation(),
			Agent->GetActorTransform()
		);
		ULearningAgentsObservations::MakeVelocityObservation(
			InObservationObject,
			Agent->GetVelocity(),
			Agent->GetActorTransform()
		);
	}

	
	OutObservationObjectElement = CharacterRootElement;
	//memcpy(&OutObservationObjectElement, &CharacterRootElement, sizeof(int32));
}

void UPursuerInteractor::SpecifyAgentAction_Implementation(FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema)
{
	ActionRootElement = ULearningAgentsActions::SpecifyVelocityAction(InActionSchema, 1.0f);
	OutActionSchemaElement = ActionRootElement;
}

void UPursuerInteractor::PerformAgentActions_Implementation(const ULearningAgentsActionObject* InActionObject, const TArray<FLearningAgentsActionObjectElement>& InActionObjectElements, const TArray<int32>& AgentIds)
{
	for(const int32 AgentId : AgentIds)
	{
		APursuerAgent* Agent = Cast<APursuerAgent>(GetAgent(AgentId));
		if(!Agent)
		{
			continue;
		}

		FVector MoveDir = FVector::ZeroVector;
		ULearningAgentsActions::MakeVelocityAction(
			const_cast<ULearningAgentsActionObject*>(InActionObject),
			MoveDir,
			Agent->GetActorTransform()
		);
		Agent->AddMovementInput(MoveDir);
	}
}
