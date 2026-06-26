// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerTrainingEnvironment.h"
#include "Pursuer/PursuerAgent.h"
#include "Evader/EvaderAgent.h"
#include "Evader/EvaderGoal.h"
#include "LearningAgentsRewards.h"
#include "Kismet/KismetMathLibrary.h"

void UPursuerTrainingEnvironment::GatherAgentRewards_Implementation(TArray<float>& OutRewards, const TArray<int32>& AgentIds)
{
	TArray<float> RewardArrays;
	for(int32 AgentId : AgentIds)
	{
		APursuerAgent* CurrentAgent = Cast<APursuerAgent>(GetAgent(AgentId));

		//float DistanceThreshold = -1.0f * ULearningAgentsRewards::MakeRewardOnLocationDifferenceBelowThreshold(EvaderActor->GetActorLocation(), GoalActor->GetActorLocation(), 100.0f, 10.0f);

		float DistanceToEvader = FVector::Dist(EvaderActor->GetActorLocation(), CurrentAgent->GetActorLocation());
		float Reward = -0.001f * DistanceToEvader;
		RewardArrays.Add(Reward);
	}

	OutRewards = RewardArrays;
}

void UPursuerTrainingEnvironment::GatherAgentCompletions_Implementation(TArray<ELearningAgentsCompletion>& OutCompletions, const TArray<int32>& AgentIds)
{
	TArray<ELearningAgentsCompletion> CompletionArrays;
	bool bEpisodeShouldEnd = false;

	float EvaderGoalDist = FVector::Dist(EvaderActor->GetActorLocation(), GoalActor->GetActorLocation());
	if(EvaderGoalDist < 150.0f)
	{
		bEpisodeShouldEnd = true;
	}

	if(!bEpisodeShouldEnd)
	{
		for(int32 AgentId : AgentIds)
		{
			APursuerAgent* CurrentAgent = Cast<APursuerAgent>(GetAgent(AgentId));

			float AgentEvaderDist = FVector::Dist(EvaderActor->GetActorLocation(), CurrentAgent->GetActorLocation());
			if(AgentEvaderDist < 150.0f)
			{
				bEpisodeShouldEnd = true;
				break;
			}
		}
	}
	for(int32 AgentId : AgentIds)
	{
		if(bEpisodeShouldEnd)
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

		CurrentAgent->ResetActor();
	}
	EvaderActor->ResetActor();
	GoalActor->ResetActor();
}

FVector UPursuerTrainingEnvironment::GetRandomPointInMap(const FVector& Origin, float Radius)
{
	float RandomX = UKismetMathLibrary::RandomFloatInRange(Origin.X - Radius, Origin.X + Radius);
	float RandomY = UKismetMathLibrary::RandomFloatInRange(Origin.Y - Radius, Origin.Y + Radius);

	return FVector(RandomX, RandomY, Origin.Z);
}
