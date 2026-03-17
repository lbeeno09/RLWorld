// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerTrainingEnv.h"
#include "Pursuer/PursuerAgent.h"
#include "LearningAgentsRewards.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"

void UPursuerTrainingEnv::GatherAgentReward_Implementation(float& OutReward, const int32 AgentId)
{
	APursuerAgent* RewardActor = Cast<APursuerAgent>(GetAgent(AgentId));
	if(!RewardActor || !TargetObject)
	{
		OutReward = 0.0f;
		return;
	}
	
	const FVector ToTarget = TargetObject->GetActorLocation() - RewardActor->GetActorLocation();
	const float Dist = ToTarget.Size();

	// Closeness
	float ProximityReward = 1.0f - FMath::Clamp(Dist / 6000.0f, 0.0f, 1.0f);

	// Directional
	FVector Velocity = RewardActor->GetVelocity();
	Velocity.Normalize();
	FVector DirToTarget = ToTarget;
	DirToTarget.Normalize();

	float DirectionalReward = FVector::DotProduct(Velocity, DirToTarget);
	DirectionalReward = FMath::Max(0.0f, DirectionalReward);

	float TargetDistToGoal = FVector::Dist(TargetObject->GetActorLocation(), TargetObject->CurrentGoalLocation);

	float GoalFailurePenalty = 0.0f;
	if(TargetDistToGoal < 1000.0f)
	{
		GoalFailurePenalty = 1.0f - (TargetDistToGoal / 1000.0f);
	}

	float BaseReward = (ProximityReward * 0.7f) + (DirectionalReward * 0.3f);

	OutReward = BaseReward - (GoalFailurePenalty * 2.0f);
}

void UPursuerTrainingEnv::GatherAgentCompletion_Implementation(ELearningAgentsCompletion& OutCompletion, const int32 AgentId)
{
	APursuerAgent* CompActor = Cast<APursuerAgent>(GetAgent(AgentId));
	if(!CompActor || !TargetObject)
	{
		OutCompletion = ELearningAgentsCompletion::Running;
		return;
	}

	float DistToTarget = FVector::Dist(CompActor->GetActorLocation(), TargetObject->GetActorLocation());
	const float TargetDistToGoal = FVector::Dist(TargetObject->GetActorLocation(), TargetObject->CurrentGoalLocation);

	if(DistToTarget < 150.0f)
	{
		OutCompletion = ELearningAgentsCompletion::Termination;
	}
	if(TargetDistToGoal < 200.0f)
	{
		OutCompletion = ELearningAgentsCompletion::Termination;

	}

	OutCompletion = ELearningAgentsCompletion::Running;
}

void UPursuerTrainingEnv::ResetAgentEpisode_Implementation(const int32 AgentId) 
{
	//APursuerAgent* ResetActor = Cast<APursuerAgent>(GetAgent(AgentId));
	//if(ResetActor)
	//{
	//	FVector Location = FVector(0.0f, 0.0f, 92.0f);

	//	ResetActor->ResetAgent(Location, FRotator::ZeroRotator);
	//}
}
