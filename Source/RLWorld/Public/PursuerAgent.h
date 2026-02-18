// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "PursuerAgent.generated.h"

UCLASS(Abstract)
class RLWORLD_API APursuerAgent : public ACharacterBase
{
	GENERATED_BODY()

protected:
	/** Default walk speed when not sprinting or recovering */
	UPROPERTY(EditAnywhere, Category = "Walk")
	float WalkSpeed = 250.0f;

protected:
	/** Gameplay initialization */
	virtual void BeginPlay() override;

};
