// Fill out your copyright notice in the Description page of Project Settings.

#include "Evader/EnvQueryContext_Goal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/GameplayStatics.h"

void UEnvQueryContext_Goal::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	TArray<AActor*> FoundGoals;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Goal"), FoundGoals);

	if(FoundGoals.Num() > 0)
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, FoundGoals[0]);
	}
}
