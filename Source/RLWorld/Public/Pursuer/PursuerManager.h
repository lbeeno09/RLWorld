// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PursuerManager.generated.h"

UCLASS()
class RLWORLD_API APursuerManager : public AActor
{
	GENERATED_BODY()
	
public:
	APursuerManager();

protected:
	virtual void Tick(float DeltaTime) override;
};
