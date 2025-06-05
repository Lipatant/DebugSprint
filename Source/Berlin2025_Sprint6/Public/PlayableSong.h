// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fstream>
#include "CoreMinimal.h"
#include "PlayableSongChart.h"
#include "UObject/NoExportTypes.h"

#include "PlayableSong.generated.h"

UCLASS(Blueprintable)
class BERLIN2025_SPRINT6_API UPlayableSong : public UObject
{
	GENERATED_BODY()

public:
	UPlayableSong();
	~UPlayableSong();
	void Initialize(const FString FilePath);

	UPROPERTY(BlueprintReadWrite, EditAnywhere);
	TArray<UPlayableSongChart*> Charts;
};
