// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "FileReader.generated.h"

UCLASS()
class BERLIN2025_SPRINT6_API UFileReader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Reads a file from its FilePath.
	UFUNCTION(BlueprintCallable, Category="File")
	static FString ReadStringFromFile(FString FilePath, bool& Success);
};
