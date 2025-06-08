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

	int32 BarIndex = 0;
	UPlayableSongChart* Chart = nullptr;
	TArray<FString> Lines;
	int32 Index = 0;
	bool InNoteSection = false;
	TArray<FString> StepsInBar;

	FileContent.ParseIntoArrayLines(Lines);
	for (FString& Line: Lines)
	{
		Line.TrimStartAndEndInline();
		if (Line.StartsWith("#NOTEDATA:"))
		{
			if (Chart) {
				Charts.Add(Chart);
			}
			Chart = NewObject<UPlayableSongChart>(this);
		}
		else if (Chart)
		{
			if (Line.StartsWith("#BPMS:"))
			{
				FString BPMData = Line.Mid(6);
				TArray<FString> BPMChangeDataList;
				BPMData.ParseIntoArray(BPMChangeDataList, ",", true);
				for (const FString& BPMChangeData : BPMChangeDataList)
				{
					FString BeatData;
					FString BPMData;
					if (Pair.Split("=", &BeatData, &BPMData))
					{
						Chart->BPMChanges.Add(FCString::Atof(*BeatData), FCString::Atof(*BPMData));
					}
				}
			}
			else if (Line.StartsWith("#DESCRIPTION:"))
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
			else if (Line.StartsWith("#NOTES:"))
			{
				BarIndex = 0;
				Index = 0;
				InNoteSection = true;
				StepsInBar.Empty();
			}
			else if (Line.StartsWith("#OFFSET:"))
			{
				Chart->Offset = FCString::Atof(*Line.Mid(8));
			}
			else if (Line.StartsWith("#STEPSTYPE:"))
			{
				int32 EndIndex = Line.Find(";", ESearchCase::IgnoreCase, ESearchDir::FromStart, 13);
				if (EndIndex != INDEX_NONE) {
					Chart->StepStype = Line.Mid(11, EndIndex - 11);
				}
			}
			else if (InNoteSection)
			{
				if (Line == ";")
				{
					InNoteSection = false;
				}
				else if (Line == ",")
				{
					int StepCountInBar = StepsInBar.Num();
					for (int i = 0; i < StepCountInBar; i++)
					{
						const FString& StepData = StepsInBar[i];
						if (StepData.Len() < 5)
						{
							continue;
						}
						float Beat = BarIndex * 4.0f + 4.0f * (i / static_cast<float>(StepCountInBar));
						float Delta = Chart->GetDeltaFromBeat(Beat);
						bool Valid = false;
						EChartStepType Content[5];
						for (uint8 j = 0; j < 5; j++)
						{
							switch (StepsInBar[i][j])
							{
							case '0':
								Content[j] = EChartStepType::NONE;
								break;
							case '1':
								Content[j] = EChartStepType::TAP;
								break;
							case '2':
								Content[j] = EChartStepType::HOLD;
								break;
							case '3':
								Content[j] = EChartStepType::END;
								break;
							case '4':
								Content[j] = EChartStepType::ROLL;
								break;
							default:
								Valid = false;
								break;
							}
						}
						if (Valid)
						{
							for (uint8 j = 0; j < 5; j++)
							{
								if (Content[j] == EChartStepType::NONE)
								{
									continue;
								}
								FChartStep Step;
								Step.Delta = Delta;
								Step.Index = Index++;
								Step.Position = j;
								Step.StepType = Content[j];
								Chart->Steps.Add(Step);
							}
						}
					}
					BarIndex++;
					StepsInBar.Empty();
				}
				else
				{
					StepsInBar.Add(Line);
				}
			}
		}
	}
	if (Chart) {
		Charts.Add(Chart);
	}
	return true;
}
