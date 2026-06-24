// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LearningAgentsCommunicator.h"
#include "PursuerManager.generated.h"

UCLASS()
class RLWORLD_API APursuerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	APursuerManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ULearningAgentsManager> PursuerManager;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRunInference = false;

	// Pursuer Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class APursuerAgent*> PursuerAgents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPursuerInteractor* PursuerInteractor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsPolicy* PursuerPolicy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsCritic* PursuerCritic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPursuerTrainingEnvironment* PursuerTrainingEnv;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FLearningAgentsCommunicator PursuerCommunicator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsPPOTrainer* PursuerPPOTrainer;

	// Evader Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AEvaderAgent* EvaderAgent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AEvaderGoal* GoalActor;
};
