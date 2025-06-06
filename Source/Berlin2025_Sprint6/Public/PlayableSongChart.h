// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fstream>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "PlayableSongChart.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BERLIN2025_SPRINT6_API UPlayableSongChart : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Description = "";
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Meter = 1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString StepStype = "";
};
