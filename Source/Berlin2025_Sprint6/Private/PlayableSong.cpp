// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableSong.h"

#include "ChartStep.h"
#include "ChartStepType.h"

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
	int32 Index = 0;
	int32 TimeSinceLast = 0;

	FileContent.ParseIntoArrayLines(Lines);
	for (FString& Line: Lines)
	{
		if (Line.StartsWith("#NOTEDATA:;"))
		{
			if (Chart) {
				Charts.Add(Chart);
			}
			Chart = NewObject<UPlayableSongChart>(this);
			Index = 0;
			TimeSinceLast = 0;
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
			else if (Line.StartsWith(","))
			{
				FChartStep Step = {
					Index, 0, EChartStepType::NONE, 0
				};
				Chart->Steps.Add(Step);
				Index++;
			}
			else if (Line.Len() >= 5)
			{
				bool Valid = true;
				EChartStepType Content[5];
				for (uint8 i = 0; i < 5; i++)
				{
					switch (Line[i])
					{
					case '0':
						Content[i] = EChartStepType::NONE;
						break;
					case '1':
						Content[i] = EChartStepType::TAP;
						break;
					case '2':
						Content[i] = EChartStepType::HOLD;
						break;
					case '3':
						Content[i] = EChartStepType::END;
						break;
					case '4':
						Content[i] = EChartStepType::ROLL;
						break;
					default:
						Valid = false;
						break;
					}
					if (!Valid)
					{
						break;
					}
				}
				if (Valid)
				{
					for (uint8 i = 0; i < 5; i++)
					{
						if (Content[i] == EChartStepType::NONE) {
							continue;
						}
						FChartStep Step = {
							Index, i, Content[i], TimeSinceLast
						};
						Chart->Steps.Add(Step);
						Index++;
						TimeSinceLast = 0;
					}
					TimeSinceLast++;
				}
			}
		}
	}
	if (Chart) {
		Charts.Add(Chart);
	}
	return true;
}
