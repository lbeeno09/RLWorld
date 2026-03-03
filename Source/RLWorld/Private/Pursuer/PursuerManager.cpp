// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APursuerManager::APursuerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PursuerManager = CreateDefaultSubobject<ULearningAgentsManager>(TEXT("Pursuer Manager"));
	PursuerManager->SetMaxAgentNum(32);
}

void APursuerManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(RootComponent)
	{
		RootComponent->ComponentTags.AddUnique(FName("PursuerManager"));
	}
}

// Called when the game starts or when spawned
void APursuerManager::BeginPlay()
{
	Super::BeginPlay();

	// Get Actors
	TArray<AActor*> TargetList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APursuerAgent::StaticClass(), TargetList);
	for(AActor* Target : TargetList)
	{
		APursuerAgent* PursuerTarget = Cast<APursuerAgent>(Target);

		PursuerActors.AddUnique(PursuerTarget);
		AddTickPrerequisiteActor(PursuerTarget);
	}


	// Get Targets
	EvaderActor = Cast<AEvaderAgent>(UGameplayStatics::GetActorOfClass(GetWorld(), AEvaderAgent::StaticClass()));

	// Make Interactor
	PursuerInteractor = Cast<UPursuerInteractor>(UPursuerInteractor::MakeInteractor(PursuerManager, UPursuerInteractor::StaticClass(), FName("PursuerInteractor")));
	PursuerInteractor->SetTargetObject(EvaderActor);

	// Make Policy
	ULearningAgentsInteractor* TempInteractor = Cast<ULearningAgentsInteractor>(PursuerInteractor);
	PursuerPolicy = ULearningAgentsPolicy::MakePolicy(PursuerManager, TempInteractor, ULearningAgentsPolicy::StaticClass(), FName("PursuerPolicy"), PursuerDAEncoder, PursuerDAPolicy, PursuerDADecoder, !bRunInference, !bRunInference, !bRunInference, PursuerPolicySettings);

	// Make Critic
	ULearningAgentsPolicy* TempPolicy = Cast<ULearningAgentsPolicy>(PursuerPolicy);
	PursuerCritic = ULearningAgentsCritic::MakeCritic(PursuerManager, TempInteractor, TempPolicy, ULearningAgentsCritic::StaticClass(), FName("PursuerCritic"), PursuerDACritic, !bRunInference, PursuerCriticSettings);

	// Make Training Environment
	PursuerTrainingEnv = Cast<UPursuerTrainingEnv>(ULearningAgentsTrainingEnvironment::MakeTrainingEnvironment(PursuerManager, ULearningAgentsTrainingEnvironment::StaticClass(), FName("PursuerTrainingEnvironment")));
	PursuerTrainingEnv->SetTargetObject(EvaderActor);

	// Spawn Shared Memory Training Process
	FLearningAgentsSharedMemoryTrainerProcess TrainerProcess =  ULearningAgentsCommunicatorLibrary::SpawnSharedMemoryTrainingProcess(PursuerTrainerProcessSettings, PursuerSharedMemorySettings);
	PursuerCommunicator = ULearningAgentsCommunicatorLibrary::MakeSharedMemoryCommunicator(TrainerProcess, PursuerTrainerProcessSettings, PursuerSharedMemorySettings);

	// Make PPO Trainer
	ULearningAgentsTrainingEnvironment* TempTrainingEnv = Cast<ULearningAgentsTrainingEnvironment>(PursuerTrainingEnv);
	PursuerPPOTrainer = ULearningAgentsPPOTrainer::MakePPOTrainer(PursuerManager, TempInteractor, TempTrainingEnv, PursuerPolicy, PursuerCritic, PursuerCommunicator, ULearningAgentsPPOTrainer::StaticClass(), FName("PursuerPPOTrainer"), PursuerTrainerSettings);

	// Reset Logic
	if(bRunInference)
	{
		for(APursuerAgent* Actor : PursuerActors)
		{
			Actor->ResetToSpawn();
		}
	}
}

// Called every frame
void APursuerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bRunInference)
	{
		PursuerPolicy->RunInference(1.0f);
	}
	else
	{
		PursuerPPOTrainer->RunTraining(PursuerTrainerTrainingSettings, PursuerTrainingGameSettings, true, true);
	}
}

