// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Evader/EvaderAgent.h"
#include "LearningAgentsTrainingEnvironment.h"
#include "LearningAgentsCompletions.h"
#include "PursuerTrainingEnv.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API UPursuerTrainingEnv : public ULearningAgentsTrainingEnvironment
{
	GENERATED_BODY()
	
public:
	void SetTargetObject(AEvaderAgent* Target) { TargetObject = Target; }

protected:
	virtual void GatherAgentReward_Implementation(float& OutReward, const int32 AgentId) override;

	virtual void GatherAgentCompletion_Implementation(ELearningAgentsCompletion& OutCompletion, const int32 AgentId) override;

	virtual void ResetAgentEpisode_Implementation(const int32 AgentId) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AEvaderAgent> TargetObject;
};
