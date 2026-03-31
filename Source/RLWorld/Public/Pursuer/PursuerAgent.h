// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PursuerAgent.generated.h"

UCLASS()
class RLWORLD_API APursuerAgent : public ACharacter
{
	GENERATED_BODY()

public:
	APursuerAgent();

	UFUNCTION(BlueprintCallable, Category = "Learning Agents")
	void SetAgentID(int32 InID) { MyAgentID = InID; }

	UPROPERTY(BlueprintReadOnly, Category="Learning Agents")
	int32 MyAgentID = -1;

protected:
	/** Gameplay initialization */
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;
};
