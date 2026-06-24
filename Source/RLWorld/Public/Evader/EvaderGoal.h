// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EvaderGoal.generated.h"

UCLASS()
class RLWORLD_API AEvaderGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	AEvaderGoal();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
		
};
