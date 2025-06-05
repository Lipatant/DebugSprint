// Fill out your copyright notice in the Description page of Project Settings.

#include "FileReader.h"
#include "HAL/PlatformFileManager.h"

FString UFileReader::ReadStringFromFile(FString FilePath, bool& Success)
{
	FString Output = "";

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath) || !FFileHelper::LoadFileToString(Output, *FilePath))
	{
		Success = false;
		return "";
	}
	Success = true;
	return Output;
}