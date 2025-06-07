// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableSong.h"

UPlayableSong::UPlayableSong()
{
}

UPlayableSong::~UPlayableSong()
{
}

bool UPlayableSong::Initialize(const FString &FilePath)
{
	FString FullPath = FPaths::ProjectContentDir() + "PlayableSongs/" + FilePath;
	FString FileContent;

	if (!FPaths::FileExists(FullPath)) {
		UE_LOG(LogTemp, Error, TEXT("Couldn't find file: %s."), *FullPath);
		return false;
	}
	if (!FFileHelper::LoadFileToString(FileContent, *FullPath))
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't load file: %s."), *FullPath);
		return false;
	}

	UPlayableSongChart* Chart = nullptr;
	TArray<FString> Lines;

	FileContent.ParseIntoArrayLines(Lines);
	for (FString& Line: Lines)
	{
		if (Line.StartsWith("#NOTEDATA:;"))
		{
			if (Chart) {
				Charts.Add(Chart);
			}
			Chart = NewObject<UPlayableSongChart>(this);
		}
		else if (Chart)
		{
			if (Line.StartsWith("#DESCRIPTION:"))
			{
				int32 EndIndex = Line.Find(";", ESearchCase::IgnoreCase, ESearchDir::FromStart, 13);
				if (EndIndex != INDEX_NONE) {
					Chart->Description = Line.Mid(13, EndIndex - 13);
				}
			}
			else if (Line.StartsWith("#METER:"))
			{
				Chart->Meter = FCString::Atoi(*Line.Mid(7));
			}
			else if (Line.StartsWith("#STEPSTYPE:"))
			{
				int32 EndIndex = Line.Find(";", ESearchCase::IgnoreCase, ESearchDir::FromStart, 13);
				if (EndIndex != INDEX_NONE) {
					Chart->StepStype = Line.Mid(11, EndIndex - 11);
				}
			}
		}
	}
	if (Chart) {
		Charts.Add(Chart);
	}
	return true;
}