// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableSong.h"

#include "ChartStep.h"
#include "ChartStepType.h"

enum ESection {
	BPMS,
	NONE,
	NOTES,
};

UPlayableSong::UPlayableSong()
{
}

UPlayableSong::~UPlayableSong()
{
}

bool UPlayableSong::Initialize(const FString& FilePath)
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
	ESection Section = ESection::NONE;
	TArray<FString> StepsInBar;
	EChartStepType StepsInMemory[5] = {
		EChartStepType::NONE, EChartStepType::NONE, EChartStepType::NONE, EChartStepType::NONE, EChartStepType::NONE
	};

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
			Section = ESection::NONE;
		}
		else if (Chart)
		{
			if (Section == ESection::NONE) {
				if (Line.StartsWith("#BPMS:"))
				{
					Chart->ParseAndAddBPM(Line.Mid(6));
					Section = ESection::BPMS;
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
					Section = ESection::NOTES;
					StepsInBar.Empty();
					for (uint8 i = 0; i < 5; i++) {
						StepsInMemory[i] = EChartStepType::NONE;
					}
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
			}
			else
			{
				switch (Section)
				{
				case ESection::BPMS:
					Chart->ParseAndAddBPM(Line);
					break;
				case ESection::NOTES:
					if ((Line == ",") || (Line == ";"))
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
							bool Valid = true;
							EChartStepType Content[5];
							for (uint8 j = 0; j < 5; j++)
							{
								switch (StepData[j])
								{
								case '0':
									Content[j] = StepsInMemory[j];
									break;
								case '1':
									Content[j] = EChartStepType::TAP;
									StepsInMemory[j] = EChartStepType::NONE;
									break;
								case '2':
									Content[j] = EChartStepType::HOLD;
									StepsInMemory[j] = EChartStepType::HOLD_BODY;
									break;
								case '3':
									Content[j] = EChartStepType::END;
									StepsInMemory[j] = EChartStepType::NONE;
									break;
								case '4':
									Content[j] = EChartStepType::ROLL;
									StepsInMemory[j] = EChartStepType::ROLL_BODY;
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
									switch (Content[j])
									{
									case EChartStepType::NONE:
										Content[j] = StepsInMemory[j];
										break;
									case EChartStepType::TAP:
										StepsInMemory[j] = EChartStepType::NONE;
										break;
									case EChartStepType::HOLD:
										StepsInMemory[j] = EChartStepType::HOLD_BODY;
										break;
									case EChartStepType::END:
										StepsInMemory[j] = EChartStepType::NONE;
										break;
									case EChartStepType::ROLL:
										StepsInMemory[j] = EChartStepType::ROLL_BODY;
										break;
									}
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
					break;
				}
				if (Line == TEXT(";") || Line.EndsWith(";"))
				{
					Section = ESection::NONE;
				}
			}
		}
	}
	if (Chart) {
		Charts.Add(Chart);
	}
	return true;
}
