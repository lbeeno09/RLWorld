// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EvaderAgent.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API AEvaderAgent : public ACharacter
{
	GENERATED_BODY()

public:
	AEvaderAgent();

	void ResetActor();
	void SetSpawnLocation(FVector Location);

private:
	FVector SpawnLocation;
};
