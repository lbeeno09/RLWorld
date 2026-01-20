// Fill out your copyright notice in the Description page of Project Settings.


#include "PursuerManager.h"
#include "PursuerInteractor.h"

// Sets default values
APursuerManager::APursuerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Manager Component
	ManagerComponent = CreateDefaultSubobject<ULearningAgentsManager>(TEXT("LearningAgentsManager"));

	if(ManagerComponent)
	{
		ManagerComponent->ComponentTags.Empty();
		ManagerComponent->ComponentTags.Add(FName("PursuerManager"));
	}
}

// Called when the game starts or when spawned
void APursuerManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APursuerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APursuerManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(ManagerComponent)
	{
		ManagerComponent->RemoveAllAgents();
	}
}
