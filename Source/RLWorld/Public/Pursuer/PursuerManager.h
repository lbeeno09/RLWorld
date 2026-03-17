// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsManager.h"
#include "LearningArray.h"
#include "GameFramework/Actor.h"

#include "LearningAgentsInteractor.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsPPOTrainer.h"
#include "LearningAgentsCommunicator.h"
#include "PursuerManager.generated.h"

class APursuerAgent;
class AEvaderAgent;
class UPursuerInteractor;
class UPursuerTrainingEnv;
class ULearningAgentsPolicy;
class ULearningAgentsCritic;
class ULearningAgentsPPOTrainer;


UCLASS()
class RLWORLD_API APursuerManager : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APursuerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleAgentReset(const int32 AgentId);


	// Core Manager
	UPROPERTY(VisibleAnywhere, Category="Learning Agents")
	ULearningAgentsManager* PursuerManager;

	// RL Component
	UPROPERTY(Transient)
	UPursuerInteractor* PursuerInteractor;

	UPROPERTY(Transient)
	UPursuerTrainingEnv* PursuerTrainingEnv;

	UPROPERTY(Transient)
	ULearningAgentsPolicy* PursuerPolicy;

	UPROPERTY(Transient)
	ULearningAgentsCritic* PursuerCritic;

	UPROPERTY(Transient)
	ULearningAgentsPPOTrainer* PursuerPPOTrainer;

	// Data Assetss
	UPROPERTY(EditAnywhere, Category = "Learning Agents|Data Assets")
	ULearningAgentsNeuralNetwork* PursuerDAEncoder;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Data Assets")
	ULearningAgentsNeuralNetwork* PursuerDAPolicy;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Data Assets")
	ULearningAgentsNeuralNetwork* PursuerDADecoder;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Data Assets")
	ULearningAgentsNeuralNetwork* PursuerDACritic;

	// Actors
	UPROPERTY(EditAnywhere, Category = "Learning Agents|Evaders")
	AEvaderAgent* EvaderActor;


	// Settings
	UPROPERTY(EditAnywhere, Category = "Learning Agents|Settings")
	bool bRunInference = false;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Settings")
	FLearningAgentsPolicySettings PursuerPolicySettings;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Settings")
	FLearningAgentsCriticSettings PursuerCriticSettings;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Settings")
	FLearningAgentsPPOTrainerSettings PursuerTrainerSettings;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Settings")
	FLearningAgentsPPOTrainingSettings PursuerTrainingSettings;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Settings")
	FLearningAgentsTrainingGameSettings PursuerGameSettings;

	// Communicator Variables
	UPROPERTY(EditAnywhere, Category = "Learning Agents|Communicator")
	FLearningAgentsTrainerProcessSettings PursuerTrainerProcessSettings;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Communicator")
	FLearningAgentsSharedMemoryCommunicatorSettings PursuerSharedMemorySettings;

	FLearningAgentsCommunicator PursuerCommunicator;
};
