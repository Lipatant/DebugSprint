// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChartStep.h"
#include "UObject/NoExportTypes.h"

#include "PlayableSongChart.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BERLIN2025_SPRINT6_API UPlayableSongChart : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart")
	FString Description = "";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart")
	int Meter = 1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart")
	FString StepStype = "";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart")
	TArray<FChartStep> Steps;
};
