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
	FString FullPath = FPaths::ProjectSavedDir() + "PlayableSongs/" + FilePath;
	FString FileContent;

	if (!FFileHelper::LoadFileToString(FileContent, *FullPath))
	{
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
				Chart->Description = Line.Mid(13, Line.Find(";", ESearchCase::IgnoreCase, ESearchDir::FromStart, 13));
			}
			else if (Line.StartsWith("#METER:"))
			{
				Chart->Meter = FCString::Atoi(*Line.Mid(7));
			}
			else if (Line.StartsWith("#STEPSTYPE:"))
			{
				Chart->StepStype = Line.Mid(11, Line.Find(";", ESearchCase::IgnoreCase, ESearchDir::FromStart, 11));
			}
		}
	}
	if (Chart) {
		Charts.Add(Chart);
	}
	return true;
}