// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "PursuerInteractor.generated.h"

class AEvaderAgent;
class APursuerAgent;

/**
 * 
 */
UCLASS()
class RLWORLD_API UPursuerInteractor : public ULearningAgentsInteractor
{
	GENERATED_BODY()

public:
	void SetTargetObject(AEvaderAgent* InTarget) { TargetObject = InTarget; }

protected:
	virtual void SpecifyAgentObservation_Implementation(FLearningAgentsObservationSchemaElement& OutObservationSchemaElement, ULearningAgentsObservationSchema* InObservationSchema) override;

	virtual void GatherAgentObservation_Implementation(FLearningAgentsObservationObjectElement& OutObservationObjectElement, ULearningAgentsObservationObject* InObservationObject, const int32 AgentId) override;

	virtual void SpecifyAgentAction_Implementation(FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema) override;

	virtual void PerformAgentAction_Implementation(const ULearningAgentsActionObject* InActionObject, const FLearningAgentsActionObjectElement& InActionObjectElement, const int32 AgentId) override;

private:
	UPROPERTY()
	AEvaderAgent* TargetObject;
};
