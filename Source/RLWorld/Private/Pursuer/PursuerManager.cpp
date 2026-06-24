// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerManager.h"
#include "Pursuer/PursuerAgent.h"
#include "Pursuer/PursuerInteractor.h"
#include "Pursuer/PursuerTrainingEnvironment.h"
#include "Evader/EvaderAgent.h"
#include "Evader/EvaderGoal.h"
#include "LearningAgentsManager.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
//#include "LearningAgentsCommunicator.h"
#include "LearningAgentsPPOTrainer.h"
#include "Kismet/GameplayStatics.h"

APursuerManager::APursuerManager()
{
	PrimaryActorTick.bCanEverTick = true;

	PursuerManager = CreateDefaultSubobject<ULearningAgentsManager>(TEXT("Pursuer Manager"));
}

void APursuerManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Registration of Agents to Learn to the Manager
	TArray<AActor*> FoundAgents;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APursuerAgent::StaticClass(), FoundAgents);
	for(AActor* FoundAgent : FoundAgents)
	{
		APursuerAgent* Pursuer = Cast<APursuerAgent>(FoundAgent);
		Pursuer->SetSpawnLocation(Pursuer->GetActorLocation());
		PursuerAgents.Add(Pursuer);
		PursuerManager->AddAgent(Pursuer);
		AddTickPrerequisiteActor(Pursuer);
	}

	// Get Evader for Pursuers to capture
	EvaderAgent = Cast<AEvaderAgent>(UGameplayStatics::GetActorOfClass(GetWorld(), AEvaderAgent::StaticClass()));
	EvaderAgent->SetSpawnLocation(EvaderAgent->GetActorLocation());
	GoalActor = Cast<AEvaderGoal>(UGameplayStatics::GetActorOfClass(GetWorld(), AEvaderGoal::StaticClass()));

	// Setup Interactor
	ULearningAgentsManager* Manager = PursuerManager.Get();
	PursuerInteractor = Cast<UPursuerInteractor>(UPursuerInteractor::MakeInteractor(Manager, UPursuerInteractor::StaticClass(), FName("PursuerInteractor")));
	PursuerInteractor->EvaderActor = EvaderAgent;
	PursuerInteractor->GoalActor = GoalActor;

	// Setup Policy
	ULearningAgentsInteractor* Interactor = Cast<ULearningAgentsInteractor>(PursuerInteractor);
	PursuerPolicy = ULearningAgentsPolicy::MakePolicy(Manager, Interactor, ULearningAgentsPolicy::StaticClass(), FName("PursuerPolicy"));

	// Setup Critic
	PursuerCritic = ULearningAgentsCritic::MakeCritic(Manager, Interactor, PursuerPolicy, ULearningAgentsCritic::StaticClass(), FName("PursuerCritic"));
	
	// Setup Training Environment
	PursuerTrainingEnv = Cast<UPursuerTrainingEnvironment>(ULearningAgentsTrainingEnvironment::MakeTrainingEnvironment(Manager, UPursuerTrainingEnvironment::StaticClass(), FName("PursuerTrainingEnv")));
	PursuerTrainingEnv->EvaderActor = EvaderAgent;
	PursuerTrainingEnv->GoalActor = GoalActor;

	// Spawn hared Memory Training Process
	FLearningAgentsSharedMemoryTrainerProcess TrainingProcess = ULearningAgentsCommunicatorLibrary::SpawnSharedMemoryTrainingProcess();
	PursuerCommunicator = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryCommunicator(TrainingProcess);

	// Setup Trainer
	ULearningAgentsTrainingEnvironment* TrainingEnv = Cast<ULearningAgentsTrainingEnvironment>(PursuerTrainingEnv);
	PursuerPPOTrainer = ULearningAgentsPPOTrainer::MakePPOTrainer(Manager, Interactor, TrainingEnv, PursuerPolicy, PursuerCritic, PursuerCommunicator, ULearningAgentsPPOTrainer::StaticClass(), FName("PursuerPPOTrainer"));

	// (Reset Locations)
	if(bRunInference)
	{
		for(APursuerAgent* PursuerAgent : PursuerAgents)
		{
			PursuerAgent->ResetActor();
		}
		EvaderAgent->ResetActor();
	}
}

void APursuerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bRunInference)
	{
		PursuerPolicy->RunInference();
	}
	else
	{
		PursuerPPOTrainer->RunTraining();
	}
}

