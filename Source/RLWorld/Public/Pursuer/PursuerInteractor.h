// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "PursuerInteractor.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API UPursuerInteractor : public ULearningAgentsInteractor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pursuit|Actor")
	class AEvaderAgent* EvaderActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pursuit|Actor")
	AActor* GoalActor;


protected:
	// --- Observations ---
	virtual void SpecifyAgentObservation_Implementation(struct FLearningAgentsObservationSchemaElement& OutObservationSchemaElement, class ULearningAgentsObservationSchema* InObservationSchema) override;
	virtual void GatherAgentObservations_Implementation(TArray<struct FLearningAgentsObservationObjectElement>& OutObservationObjectElements, class ULearningAgentsObservationObject* InObservationObject, const TArray<int32>& AgentIds) override;

	// --- Actions ---
	virtual void SpecifyAgentAction_Implementation(struct FLearningAgentsActionSchemaElement& OutActionSchemaElement, class ULearningAgentsActionSchema* InActionSchema) override;
	virtual void PerformAgentActions_Implementation(const class ULearningAgentsActionObject* InActionObject, const TArray<struct FLearningAgentsActionObjectElement>& InActionObjectElements, const TArray<int32>& AgentIds) override;

};
