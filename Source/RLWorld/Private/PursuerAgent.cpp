// Fill out your copyright notice in the Description page of Project Settings.


#include "PursuerAgent.h"
#include "Kismet/GameplayStatics.h"
#include "PursuerManager.h"

// Sets default values
APursuerAgent::APursuerAgent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APursuerAgent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("--- BeginPlay started for Agent: %s ---"), *GetName());

	TArray<AActor*> FoundManagers;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PursuerManager"), FoundManagers);
	if(FoundManagers.Num() > 0)
	{
		if(APursuerManager* ManagerActor = Cast<APursuerManager>(FoundManagers[0]))
		{
			AgentId = ManagerActor->ManagerComponent->AddAgent(this);

			UE_LOG(LogTemp, Error, TEXT("SUCCESS: Agent %s registered with ID: %d"), *GetName(), AgentId);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("FAILED: Actor with tag found, but could not Cast to APursuerManager!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("FAILED: No Actors found with tag 'PursuerManager'!"));
	}
}

// Called every frame
void APursuerAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APursuerAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

