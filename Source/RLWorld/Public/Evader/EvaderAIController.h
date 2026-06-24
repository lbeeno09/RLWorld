// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EvaderAIController.generated.h"

/**
 * 
 */
UCLASS()
class RLWORLD_API AEvaderAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEvaderAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Evader|AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

};
