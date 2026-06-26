// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsTrainer.h"
#include "LearningAgentsTraining.h"
#include "LearningAgentsCommunicator.h"
#include "LearningAgentsPPOTrainer.h"
#include "PursuerManager.generated.h"

UCLASS()
class RLWORLD_API APursuerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	APursuerManager();

	UFUNCTION(BlueprintCallable)
	void TriggerManualReset();

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
	struct FLearningAgentsPolicySettings PursuerPolicySettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsCritic* PursuerCritic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FLearningAgentsCriticSettings PursuerCriticSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPursuerTrainingEnvironment* PursuerTrainingEnv;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FLearningAgentsTrainerProcessSettings PursuerTrainerProcessSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FLearningAgentsSharedMemoryCommunicatorSettings PursuerSharedMemorySettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FLearningAgentsCommunicator PursuerCommunicator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsPPOTrainer* PursuerPPOTrainer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FLearningAgentsPPOTrainerSettings PursuerTrainerSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FLearningAgentsPPOTrainingSettings PursuerTrainerTrainingSettings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FLearningAgentsTrainingGameSettings PursuerTrainingGameSettings;

	// Data Assets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsNeuralNetwork* PursuerEncoderAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsNeuralNetwork* PursuerPolicyAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsNeuralNetwork* PursuerDecoderAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ULearningAgentsNeuralNetwork* PursuerCriticAsset;

	// Evader Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AEvaderAgent* EvaderAgent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AEvaderGoal* GoalActor;
};
