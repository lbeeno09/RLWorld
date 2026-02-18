// Fill out your copyright notice in the Description page of Project Settings.

#include "PursuerTrainingEnv.h"
#include "LearningAgentsRewards.h"
#include "LearningAgentsCompletions.h"
#include "PursuerAgent.h"
#include "Kismet/KismetMathLibrary.h"

void UPursuerTrainingEnv::GatherAgentReward(float& OutReward, const int32 AgentId)
{
	APursuerAgent* RewardActor = Cast<APursuerAgent>(GetAgent(AgentId));

	// Get Distance
	FVector ActorLocation = RewardActor->GetActorLocation();
	FVector TargetLocation = TargetObject->GetActorLocation();
	float Dist = FVector::Dist(ActorLocation, TargetLocation);

	float Reward = ULearningAgentsRewards::MakeReward(1.0 / (1.0 + (Dist / 100.0f)));

	OutReward = Reward;
}

void UPursuerTrainingEnv::GatherAgentCompletion(ELearningAgentsCompletion& OutCompletion, const int32 AgentId)
{
	APursuerAgent* CompActor = Cast<APursuerAgent>(GetAgent(AgentId));

	FVector TargetLocation = TargetObject->GetActorLocation();
	FVector ActorLocation = CompActor->GetActorLocation();

	ELearningAgentsCompletion CompletionType = ULearningAgentsCompletions::MakeCompletionOnLocationDifferenceBelowThreshold(TargetLocation, ActorLocation);

	OutCompletion = CompletionType;
}

void UPursuerTrainingEnv::ResetAgentEpisode(const int32 AgentId)
{
	APursuerAgent* ResetActor = Cast<APursuerAgent>(GetAgent(AgentId));

	ResetActor->ResetToSpawn();
}
