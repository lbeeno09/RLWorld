// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evader/EvaderAgent.h"
#include "LearningAgentsInteractor.h"
#include "LearningAgentsObservations.h"
#include "LearningAgentsActions.h"
#include "PursuerInteractor.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API UPursuerInteractor : public ULearningAgentsInteractor
{
	GENERATED_BODY()
	
protected:
	AEvaderAgent* TargetObject;

protected:
	void SpecifyAgentObservation(FLearningAgentsObservationSchemaElement& OutObservationSchemaElement, ULearningAgentsObservationSchema* InObservationSchema);

	void GatherAgentObservation(FLearningAgentsObservationObjectElement& OutObservationObjectElement, ULearningAgentsObservationObject* InObservationObject, const int32 AgentId);

	void SpecifyAgentAction(FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema);

	void PerformAgentAction(const ULearningAgentsActionObject* InActionObject, const FLearningAgentsActionObjectElement& InActionObjectAlement, const int32 AgentId);

public:
	void SetTargetObject(AEvaderAgent*& Target);
};
