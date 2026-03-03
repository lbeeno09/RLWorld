// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pursuer/PursuerAgent.h"
#include "Pursuer/PursuerInteractor.h"
#include "Pursuer/PursuerTrainingEnv.h"
#include "Evader/EvaderAgent.h"
#include "LearningAgentsManager.h"
#include "LearningAgentsInteractor.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsCommunicator.h"
#include "LearningAgentsPPOTrainer.h"
#include "GameFramework/Actor.h"
#include "PursuerManager.generated.h"

UCLASS(Abstract)
class RLWORLD_API APursuerManager : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	ULearningAgentsManager* PursuerManager;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Settings")
	bool bRunInference = false;

	TArray<APursuerAgent*> PursuerActors;
	AEvaderAgent* EvaderActor;
	UPursuerInteractor* PursuerInteractor;
	FLearningAgentsPolicySettings PursuerPolicySettings;
	ULearningAgentsPolicy* PursuerPolicy;
	FLearningAgentsCriticSettings PursuerCriticSettings;
	ULearningAgentsCritic* PursuerCritic;
	UPursuerTrainingEnv* PursuerTrainingEnv;
	FLearningAgentsTrainerProcessSettings PursuerTrainerProcessSettings;
	FLearningAgentsSharedMemoryCommunicatorSettings PursuerSharedMemorySettings;
	FLearningAgentsCommunicator PursuerCommunicator;
	FLearningAgentsPPOTrainerSettings PursuerTrainerSettings;
	ULearningAgentsPPOTrainer* PursuerPPOTrainer;
	FLearningAgentsPPOTrainingSettings PursuerTrainerTrainingSettings;
	FLearningAgentsTrainingGameSettings PursuerTrainingGameSettings;

protected:
	UPROPERTY(EditAnywhere, Category="Learning Agents|Data Assets")
	TObjectPtr<ULearningAgentsNeuralNetwork> PursuerDAEncoder;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Data Assets")
	TObjectPtr<ULearningAgentsNeuralNetwork> PursuerDAPolicy;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Data Assets")
	TObjectPtr<ULearningAgentsNeuralNetwork> PursuerDADecoder;

	UPROPERTY(EditAnywhere, Category = "Learning Agents|Data Assets")
	TObjectPtr<ULearningAgentsNeuralNetwork> PursuerDACritic;

public:	
	// Sets default values for this actor's properties
	APursuerManager();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
