// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerManager.h"
#include "Pursuer/PursuerAgent.h"
#include "Evader/EvaderAgent.h"
#include "Pursuer/PursuerInteractor.h"
#include "Pursuer/PursuerTrainingEnv.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsPPOTrainer.h"
#include "LearningCompletion.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

// Sets default values
APursuerManager::APursuerManager()
{
	PrimaryActorTick.bCanEverTick = true;

	PursuerManager = CreateDefaultSubobject<ULearningAgentsManager>(TEXT("Pursuer Manager"));
	PursuerManager->SetMaxAgentNum(32);
}

// Called when the game starts or when spawned
void APursuerManager::BeginPlay()
{
	Super::BeginPlay();

	// Target(Evader) Actors
	EvaderActor = Cast<AEvaderAgent>(UGameplayStatics::GetActorOfClass(GetWorld(), AEvaderAgent::StaticClass()));
	
	// Get Actors
	TArray<AActor*> TargetList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APursuerAgent::StaticClass(), TargetList);

	TArray<UObject*> ObjectList;
	for(AActor* Actor : TargetList)
	{
		ObjectList.Add(Actor);
	}

	TArray<int32> OutAgentIds;
	PursuerManager->AddAgents(OutAgentIds, ObjectList);


	// Setup Interactor
	ULearningAgentsInteractor* TempInteractor = ULearningAgentsInteractor::MakeInteractor(
		PursuerManager,
		UPursuerInteractor::StaticClass(),
		FName("PursuerInteractor"));

	PursuerInteractor = Cast<UPursuerInteractor>(TempInteractor);
	if(PursuerInteractor)
	{
		PursuerInteractor->SetTargetObject(EvaderActor);
	}

	// Setup Policy
	PursuerPolicy = ULearningAgentsPolicy::MakePolicy(
		PursuerManager,
		TempInteractor,
		ULearningAgentsPolicy::StaticClass(),
		FName("PursuerPolicy"),
		PursuerDAEncoder,
		PursuerDAPolicy,
		PursuerDADecoder,
		!bRunInference, !bRunInference, !bRunInference, 
		PursuerPolicySettings);

	if(!bRunInference)
	{
		// Setup Critic
		PursuerCritic = ULearningAgentsCritic::MakeCritic(
			PursuerManager,
			TempInteractor,
			PursuerPolicy,
			ULearningAgentsCritic::StaticClass(),
			FName("PursuerCritic"),
			PursuerDACritic,
			!bRunInference,
			PursuerCriticSettings);

		// Setup Training Environment
		ULearningAgentsTrainingEnvironment* TempEnv = ULearningAgentsTrainingEnvironment::MakeTrainingEnvironment(
			PursuerManager,
			UPursuerTrainingEnv::StaticClass(),
			FName("PursuerTrainingEnvironment"));

		PursuerTrainingEnv = Cast<UPursuerTrainingEnv>(TempEnv);
		if(PursuerTrainingEnv)
		{
			PursuerTrainingEnv->SetTargetObject(EvaderActor);
		}

		// Spawn Shared Memory Training Process
		FLearningAgentsSharedMemoryTrainerProcess TrainerProcess = ULearningAgentsCommunicatorLibrary::SpawnSharedMemoryTrainingProcess(
			PursuerTrainerProcessSettings,
			PursuerSharedMemorySettings);

		PursuerCommunicator = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryCommunicator(
			TrainerProcess, 
			PursuerTrainerProcessSettings,
			PursuerSharedMemorySettings);


		// Make PPO Trainer
		PursuerPPOTrainer = ULearningAgentsPPOTrainer::MakePPOTrainer(
			PursuerManager,
			TempInteractor,
			TempEnv, 
			PursuerPolicy,
			PursuerCritic,
			PursuerCommunicator, 
			ULearningAgentsPPOTrainer::StaticClass(),
			FName("PursuerPPOTrainer"),
			PursuerTrainerSettings);
	}

	//// Reset Logic
	//if(bRunInference)
	//{
	//	for(APursuerAgent* Actor : PursuerActors)
	//	{
	//		Actor->ResetToSpawn();
	//	}
	//}
}

// Called every frame
void APursuerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bRunInference && PursuerPolicy)
	{
		PursuerPolicy->RunInference(1.0f);
	}
	else if(PursuerPPOTrainer && PursuerTrainingEnv)
	{
		PursuerPPOTrainer->RunTraining(PursuerTrainingSettings, PursuerGameSettings, true, true);

		UE::Learning::ECompletionMode CompletionStatus = PursuerTrainingEnv->GetAgentCompletion(0);
		if(CompletionStatus == UE::Learning::ECompletionMode::Terminated)
		{
			HandleAgentReset(0);
			PursuerManager->ResetAgent(0);
		}

	}
}

void APursuerManager::HandleAgentReset(const int32 AgentId)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if(!NavSys || !EvaderActor)
	{
		return;
	}

	APursuerAgent* Pursuer = Cast<APursuerAgent>(PursuerManager->GetAgent(AgentId));
	if(!Pursuer)
	{
		return;
	}

	// Evader Spawn
	FNavLocation EvaderSpawn;
	if(NavSys->GetRandomReachablePointInRadius(FVector::ZeroVector, 3000.0f, EvaderSpawn))
	{
		EvaderActor->SetActorLocation(EvaderSpawn.Location);
		EvaderActor->PickNewGoal();
	}


	// Pursuer Spawn
	FNavLocation RandomLocation;
	bool bValidLocationFound = false;
	int32 RetryCount = 0;
	while(!bValidLocationFound && RetryCount < 10)
	{
		if(NavSys->GetRandomReachablePointInRadius(FVector::ZeroVector, 5000.0f, RandomLocation))
		{
			float SpawnDist = FVector::Dist(RandomLocation.Location, EvaderActor->GetActorLocation());
			if(SpawnDist > 1000.0f)
			{
				bValidLocationFound = true;
			}
		}

		RetryCount++;
	}

	FRotator RandomRot = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
	Pursuer->ResetAgent(RandomLocation.Location, RandomRot);
}