// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerTrainingEnvironment.h"
#include "Pursuer/PursuerAgent.h"
#include "Evader/EvaderAgent.h"
#include "LearningAgentsRewards.h"
#include "Kismet/KismetMathLibrary.h"

void UPursuerTrainingEnvironment::GatherAgentRewards_Implementation(TArray<float>& OutRewards, const TArray<int32>& AgentIds)
{
	TArray<float> RewardArrays;
	for(int32 AgentId : AgentIds)
	{
		APursuerAgent* CurrentAgent = Cast<APursuerAgent>(GetAgent(AgentId));

		float DistanceThreshold = ULearningAgentsRewards::MakeRewardOnLocationDifferenceBelowThreshold(EvaderActor->GetActorLocation(), GoalActor->GetActorLocation(), 100.0f, 10.0f);

		float Reward = UKismetMathLibrary::Exp(-UKismetMathLibrary::Vector_Distance(EvaderActor->GetActorLocation(), GoalActor->GetActorLocation()) / 1000.0f) + DistanceThreshold;
		RewardArrays.Add(Reward);
	}

	OutRewards = RewardArrays;
}

void UPursuerTrainingEnvironment::GatherAgentCompletions_Implementation(TArray<ELearningAgentsCompletion>& OutCompletions, const TArray<int32>& AgentIds)
{
	TArray<ELearningAgentsCompletion> CompletionArrays;
	bool hasCaught = false;
	for(int32 AgentId : AgentIds)
	{
		APursuerAgent* CurrentAgent = Cast<APursuerAgent>(GetAgent(AgentId));

		hasCaught = UKismetMathLibrary::Vector_Distance(EvaderActor->GetActorLocation(), CurrentAgent->GetActorLocation()) < 0.0 || UKismetMathLibrary::Vector_Distance(GoalActor->GetActorLocation(), EvaderActor->GetActorLocation()) < 0.0;
		if(hasCaught)
		{
			CompletionArrays.Add(ELearningAgentsCompletion::Termination);
		}
		else
		{
			CompletionArrays.Add(ELearningAgentsCompletion::Running);
		}
	}

	OutCompletions = CompletionArrays;
}

void UPursuerTrainingEnvironment::ResetAgentEpisodes_Implementation(const TArray<int32>& AgentIds)
{
	for(int32 AgentId : AgentIds)
	{
		APursuerAgent* CurrentAgent = Cast<APursuerAgent>(GetAgent(AgentId));

		// TODO: 
	}
}
