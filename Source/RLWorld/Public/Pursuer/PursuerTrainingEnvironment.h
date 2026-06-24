// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsTrainingEnvironment.h"
#include "PursuerTrainingEnvironment.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API UPursuerTrainingEnvironment : public ULearningAgentsTrainingEnvironment
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pursuit|Actor")
	class AEvaderAgent* EvaderActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pursuit|Actor")
	AActor* GoalActor;

protected:
	virtual void GatherAgentRewards_Implementation(TArray<float>& OutRewards, const TArray<int32>& AgentIds) override;
	virtual void GatherAgentCompletions_Implementation(TArray<ELearningAgentsCompletion>& OutCompletions, const TArray<int32>& AgentIds) override;
	virtual void ResetAgentEpisodes_Implementation(const TArray<int32>& AgentIds) override;

private:
	FVector GetRandomPointInMap(const FVector& Origin, float Radius);
};
