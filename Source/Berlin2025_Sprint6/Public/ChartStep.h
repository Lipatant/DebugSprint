// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChartStepType.h"

#include "ChartStep.generated.h"

USTRUCT(BlueprintType)
struct BERLIN2025_SPRINT6_API FChartStep
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Chart")
	int32 Index;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Chart")
	uint8 Position;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Chart")
	EChartStepType StepType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Chart")
	int32 TimeSinceLast;

	bool operator==(const FChartStep& Step) const
	{
		return Index == Step.Index;
	}
};

FORCEINLINE uint32 GetTypeHash(const FChartStep& Step)
{
	return ::GetTypeHash(Step.Index);
}
