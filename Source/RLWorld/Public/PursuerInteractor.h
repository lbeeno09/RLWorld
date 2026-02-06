// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
public:
	virtual void SpecifyAgentObservation_Implementation(FLearningAgentsObservationSchemaElement& OutElement, ULearningAgentsObservationSchema* chema) override;
	virtual void GatherAgentObservations_Implementation(TArray<FLearningAgentsObservationObjectElement>& OutElement, ULearningAgentsObservationObject* Obj, const TArray<int32>& AgentIds) override;
	virtual void SpecifyAgentAction_Implementation(FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema) override;
	virtual void PerformAgentActions_Implementation(const ULearningAgentsActionObject* InActionObject, const TArray<FLearningAgentsActionObjectElement>& InActionObjectElements, const TArray<int32>& AgentIds) override;

private:
	FLearningAgentsObservationSchemaElement CharacterRootElement;
	FLearningAgentsActionSchemaElement ActionRootElement;
};
