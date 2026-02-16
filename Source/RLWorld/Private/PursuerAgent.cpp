// Fill out your copyright notice in the Description page of Project Settings.

#include "PursuerAgent.h"
#include "Kismet/GameplayStatics.h"
#include "LearningAgentsManager.h"

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

