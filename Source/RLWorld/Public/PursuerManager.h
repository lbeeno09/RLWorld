// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LearningAgentsManager.h"
#include "PursuerInteractor.h"
#include "PursuerManager.generated.h"

UCLASS()
class RLWORLD_API APursuerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APursuerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
	TObjectPtr<ULearningAgentsManager> ManagerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningAgents")
	TObjectPtr<UPursuerInteractor> Interactor;
};
