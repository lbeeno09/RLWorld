// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsTrainingEnvironment.h"
#include "LearningAgentsCompletions.h"
#include "EvaderAgent.h"
#include "PursuerTrainingEnv.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API UPursuerTrainingEnv : public ULearningAgentsTrainingEnvironment
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AEvaderAgent> TargetObject;

protected:
	void GatherAgentReward(float& OutReward, const int32 AgentId);

	void GatherAgentCompletion(ELearningAgentsCompletion& OutCompletion, const int32 AgentId);

	void ResetAgentEpisode(const int32 AgentId);

public:
	void SetTargetObject(AEvaderAgent* Target) { TargetObject = Target; }
};
