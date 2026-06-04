// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerManager.h"
#include "Pursuer/PursuerAgent.h"
#include "LearningAgentsManager.h"
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
		PursuerManager->AddAgent(Pursuer);
	}

}

void APursuerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

