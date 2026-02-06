// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsPPOTrainer.h"
#include "LearningAgentsRewards.h"
#include "PursuerTrainer.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API UPursuerTrainer : public ULearningAgentsPPOTrainer
{
	GENERATED_BODY()
	
public:
	virtual void SpecifyAgentReward_Implementation(FLearningAgentsRewardSchemaElement& OutElement, ULearningAgentsRewardSchema* Schema) override;
	virtual void GatherAgentRewards_Implementation(FLearningAgentsRewardObjectElement& OutElement, ULearningAgentsRewardObject* Obj, const TArray<int32>& AgentIds) override;

private:
	FLearningAgentsRewardSchemaElement RewardRootElement;
};
