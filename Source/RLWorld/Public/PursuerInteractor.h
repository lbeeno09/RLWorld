// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "PursuerInteractor.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API UPursuerInteractor : public ULearningAgentsInteractor
{
	GENERATED_BODY()
	
protected:
	virtual void SpecifyAgentObservation()
};
