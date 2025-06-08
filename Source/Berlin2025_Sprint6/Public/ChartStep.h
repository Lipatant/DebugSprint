// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChartStepType.h"
#include "CoreMinimal.h"

#include "ChartStep.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct BERLIN2025_SPRINT6_API FChartStep
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Chart")
	uint8 Position;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Chart")
	EChartStepType StepType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Chart")
	int32 TimeSinceLast;
};
