// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayableSongChart.h"
#include "UObject/NoExportTypes.h"

#include "PlayableSong.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BERLIN2025_SPRINT6_API UPlayableSong : public UObject
{
	GENERATED_BODY()

public:
	UPlayableSong();
	~UPlayableSong();
	// Initializes the song from its FilePath.
	UFUNCTION(BlueprintCallable, Category = "Playable Song")
	bool Initialize(const FString &FilePath);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UPlayableSongChart*> Charts;
};
