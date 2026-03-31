// Fill out your copyright notice in the Description page of Project Settings.

#include "Pursuer/PursuerAgent.h"
#include "Components/CapsuleComponent.h"

APursuerAgent::APursuerAgent()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(34.f, 96.0f);

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetupAttachment(GetMesh());
}

void APursuerAgent::BeginPlay()
{
	Super::BeginPlay();

}

