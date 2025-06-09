// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChartStep.h"
#include "UObject/NoExportTypes.h"

#include "PlayableSongChart.generated.h"

USTRUCT(BlueprintType)
struct BERLIN2025_SPRINT6_API FBPMChange
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BPM Change")
	float Beat;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BPM Change")
	float BPM;
};

FORCEINLINE uint32 GetTypeHash(const FBPMChange& BPMChange)
{
	return ::GetTypeHash(BPMChange.Beat);
}

UCLASS(Blueprintable, BlueprintType)
class BERLIN2025_SPRINT6_API UPlayableSongChart : public UObject
{
	GENERATED_BODY()

public:
	UPlayableSongChart();
	~UPlayableSongChart();
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart", Transient)
	TArray<FBPMChange> BPMChanges;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart")
	FString Description = "";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart")
	int Meter = 1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart")
	float Offset = 0.0f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart")
	FString StepStype = "";
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Playable Song Chart", Transient)
	TArray<FChartStep> Steps;
	// Gets a DeltaTime from the step.
	UFUNCTION(BlueprintCallable, Category = "Playable Song Chart")
	float GetDeltaFromBeat(float const Beat);
	// Resets Steps.
	UFUNCTION(BlueprintCallable, Category = "Playable Song Chart")
	void ResetSteps();
};
