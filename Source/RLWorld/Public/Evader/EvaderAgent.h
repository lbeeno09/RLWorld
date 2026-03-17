// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "EvaderAgent.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class RLWORLD_API AEvaderAgent : public ACharacterBase
{
	GENERATED_BODY()

public:
	void PickNewGoal();

	UPROPERTY(BlueprintReadOnly)
	FVector CurrentGoalLocation;

protected:
	/** Gameplay initialization */
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Default walk speed when not sprinting or recovering */
	UPROPERTY(EditAnywhere, Category = "Walk")
	float WalkSpeed = 250.0f;
};
